#!/usr/bin/env ruby

require 'tempfile'

username = ENV['USER']
to_send = ARGV[0]

if !File.exists?(to_send)
  puts "Can't find #{to_send}"
  exit
end

mailfile = Tempfile.new('mailfile')
mailfile << "Subject: shlab submission for #{username}\n"
mailfile << File.read(to_send)
mailfile.flush

`/usr/sbin/sendmail michael.saelee@gmail.com < #{mailfile.path}`
puts "Handin complete for #{to_send}, last modified #{File.mtime(to_send)}."

mailfile.close
