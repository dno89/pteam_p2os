/**
 * @file RANSAC.h
 * @author Daniele Molinari - 238168 (daniele.molinari2@studenti.unipr.it)
 * @brief class implementing RANSAC alghorithm
 */

#ifndef	RANSAC_H
#define	RANSAC_H

#include "CConfigurable.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include <strstream>


/**
 * @class CModelT interface to implement for the ModelT type in RANSAC
 */

template<typename PointT>
class CModelT {
public:
	////typedef
	typedef PointT point_type;
	
	CModelT() {};
	CModelT(const std::vector<PointT>& points);	//construct the model, starting from NPOINTS
	virtual void CreateModel(const std::vector<PointT>& points) = 0;
	virtual double operator()(const PointT& p) = 0;			//return the distance of p from the model
	
	static int NPoints();		//the number of points needed to construct the model. This must be overridden
};

/**
 * @class RANSAC
 * @brief a class that implement RANSAC algorithm
 * @param PointT the type of the point used to construct the model
 * @param ModelT the class that represent the model, it must implement the interface of CModelT
 * @property MAX_ITERATION (unsigned int) the maximum number of iteration
 * @property MIN_CONSENSUS (unsigned int) the minimum number of consensus for a model to be valid
 * @property DISTANCE_THRESHOLD (double) the threshold above which a point is not considered part of the model
 * @property REAL_MAX_ITERATION (unsigned int) the real limit of iteration
 */
template<typename PointT, typename ModelT>
class RANSAC : public CConfigurable {
public:
	/**
	 * @fn RANSAC
	 * @brief the constructor
	 * @param maxIterations the maximum number of iteration
	 * @param minConsensus the minimum number of consensus for a model to be valid
	 * @param distanceThreshold the threshold above which a point is not considered part of the model
	 * @param realMaxIteration the real limit of iteration
	 */
	RANSAC(unsigned int maxIterations, unsigned int minConsensus, double distanceThreshold, unsigned int realMaxIteration = 1e4);
	
	/**
	 * @fn LoadPoints
	 * @brief load the points to elaborate with the Run function
	 * @param IteratorT the iterator type
	 * @param first an iterator to the first point
	 * @param last an iterator past the last point
	 */
	template<typename IteratorT>
	void LoadPoints(IteratorT first, IteratorT last);
	
	/**
	 * @fn Run
	 * @brief return the model with most consensus
	 * @param out_elements if not NULL is filled with element within the best model
	 */
	ModelT Run(std::vector<PointT>* out_elements = NULL);
private:
	std::vector<PointT> m_points;
};

template<typename PointT, typename ModelT>
RANSAC<PointT, ModelT>::RANSAC ( unsigned int maxIterations, unsigned int minConsensus, double distanceThreshold , unsigned int realMaxIteration) {
	AddProperty("MAX_ITERATION", (unsigned int)(maxIterations));
	AddProperty("REAL_MAX_ITERATION", (unsigned int)(realMaxIteration));
	AddProperty("MIN_CONSENSUS", (unsigned int)(minConsensus));
	AddProperty("DISTANCE_THRESHOLD", double(distanceThreshold));
}

template<typename PointT, typename ModelT>
template<typename IteratorT>
void RANSAC<PointT, ModelT>::LoadPoints ( IteratorT first, IteratorT last ) {
	//clear all points
	m_points.clear();
	
	int npoints = std::distance(first, last);
	if(npoints < ModelT::NPoints()) {
		//not enough point to construct the model
		std::strstream str;
		str << "RANSAC::LoadPoints ERROR: " << npoints << " passed to LoadPoints, but " << ModelT::NPoints() << " required to construct the model!\n";
		throw std::runtime_error(str.str());
	}
	
	//copy the new points
	std::copy(first, last, std::back_inserter(m_points));
}

template<typename PointT, typename ModelT>
ModelT RANSAC<PointT, ModelT>::Run ( std::vector< PointT >* out_elements ) {
	if(m_points.size() == 0) {
		throw std::runtime_error("RANSAC::Run ERROR: Run called with 0 points loaded!\n");
	}
	
	//constants
	const unsigned int MAX_ITERATION = ReadProperty<unsigned int>("MAX_ITERATION");
	const unsigned int realMAX_ITERATION = ReadProperty<unsigned int>("REAL_MAX_ITERATION");
	const unsigned int MIN_CONSENSUS = ReadProperty<unsigned int>("MIN_CONSENSUS");
	const double THRESHOLD = ReadProperty<double>("DISTANCE_THRESHOLD");
	
	//best model param
	unsigned int bestConsensus = 0;
	ModelT bestModel;
	
	//unique random params
	std::srand(std::time(NULL));
	
	unsigned int count = 0, realCount = 0;
	while(count < MAX_ITERATION && realCount < realMAX_ITERATION) {
		//this is a single iteration
		
		//select ModelT::NPOINTS distinct random points from m_points
		std::vector<PointT> seed_points;
		std::set<unsigned int> generated;
		while(seed_points.size() != ModelT::NPoints()) {
			unsigned int n = std::rand() % m_points.size();
			if(generated.count(n) == 0) {
				//a new random point is selected
				generated.insert(n);
				seed_points.push_back(m_points[n]);
			}
		}
		
		//construct the model
		ModelT model(seed_points);
		
		//count the number of consensus
		unsigned int consensus = 0;
		for(unsigned int ii = 0; ii < m_points.size(); ++ii) {
			if(model(m_points[ii]) < THRESHOLD) {
				//the point is within the model
				++consensus;
			}
		}
		
		if(consensus < MIN_CONSENSUS) {
			//discard this model, but increment the real number of iteration
			++realCount;
			continue;
		}
		
		//check if the model is the new best model
		if(consensus > bestConsensus) {
			//update the best model
			bestConsensus = consensus;
			bestModel = model;
		}
		
		//increment the number of successful iteration
		++count;
		//increment the real number of iteration
		++realCount;
	}
	
	if(realCount == realMAX_ITERATION && bestConsensus == 0) {
		///TODO: do something meaningful here
		std::strstream str;
		str << "RANSAC::Run ERROR: the algorithm tried for " << realMAX_ITERATION << " iterations without finding a model with at least " << MIN_CONSENSUS << " consensus!\n";
		throw std::runtime_error(str.str());
	}
	
	//if required fill the filtered array of points
	if(out_elements != NULL) {
		//fill the vector with the elemets that gave consensus to the best model
		for(unsigned int ii = 0; ii < m_points.size(); ++ii) {
			if(bestModel(m_points[ii]) < THRESHOLD) {
				//the point is within the model
				out_elements->push_back(m_points[ii]);
			}
		}
	}
	
	return bestModel;
}


#endif	//RANSAC_H