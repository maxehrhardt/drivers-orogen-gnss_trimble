require 'orocos'
include Orocos

if !ARGV[0]
    STDERR.puts "usage: test.rb <device name>"
    exit 1
end

ENV['PKG_CONFIG_PATH'] = "#{File.expand_path("..", File.dirname(__FILE__))}/build:#{ENV['PKG_CONFIG_PATH']}"

## Initialize orocos ##
Orocos.initialize

## Execute the task 'message_producer::Task' ##
Orocos.run 'gnss_trimble::Task' => 'test_task' do

    ## Get the task context##
    test_task = Orocos.name_service.get 'test_task'
    Orocos.conf.load_dir('../config')
    Orocos.conf.apply(test_task, [ 'ExoTer', 'Netherlands','DECOS'], :override => true)
    test_task.serial_port = ARGV[0]

    ## Configure the task ##
    test_task.configure

    ## Log all the ports
    Orocos.log_all_ports

    ## Start the task ##
    test_task.start

    #reader = test_task.messages.reader

    while true

      sleep 0.1

    end

    test_task.stop
    test_task.cleanup
end
