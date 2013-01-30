
(cl:in-package :asdf)

(defsystem "pteam_p2os-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :sensor_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ProcessedLS" :depends-on ("_package_ProcessedLS"))
    (:file "_package_ProcessedLS" :depends-on ("_package"))
  ))