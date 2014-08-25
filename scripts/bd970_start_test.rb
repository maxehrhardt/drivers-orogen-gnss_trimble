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
Orocos.run 'trimble_bd970::Task' => 'test_task' do

    ## Get the task context##
    test_task = Orocos.name_service.get 'test_task'
    test_task.serial_port = ARGV[0]
    test_task.serial_baudrate = 38400
    test_task.serial_timeout = 1.0

    test_task.geodetic_datum = "WGS84"
    test_task.utm_zone = 31
    test_task.utm_north = true

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
