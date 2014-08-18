require 'orocos'
include Orocos

## Initialize orocos ##
Orocos.initialize

## Execute the task 'message_producer::Task' ##
Orocos.run 'trimble_bd970::Task' => 'test_task' do

    ## Get the task context##
    test_task = Orocos.name_service.get 'test_task'
    
    test_task.configure
    
    ## Start the tasks ##
    test_task.start
    
    #reader = test_task.messages.reader
    
    while true
    
      sleep 0.1
      
    end
    
    test_task.stop
    
    test_task.cleanup
    
end
