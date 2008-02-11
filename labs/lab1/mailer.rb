#!/usr/bin/env ruby

### Set the following two variables to your own full name and 8 digit CWID ###

NAME = "John Doe"
CWID = "12345678"

##############################################################################

### Don't touch anything below this line! #################################### 

require 'tempfile'

DEST_EMAIL = 'lee@soi2.org'
LAB_NAME   = 'shlab'

if !File.executable?('/usr/sbin/sendmail')
  puts "Can't find sendmail binary"
  exit
end

mailfile = Tempfile.new('mailfile')
mailfile << "Subject: #{LAB_NAME} submission for #{NAME}/#{CWID}\n"

ARGV.each do |to_send| 
  if to_send.nil? or !File.exists?(to_send)
    puts "Can't find file: #{to_send}"
    exit
  else
    puts "Sending #{to_send}, last modification time #{File.mtime(to_send)}..."
    mailfile << "*" * 30 + " " +  to_send + " " + "*" * 30 + "\n\n"
    mailfile << File.read(to_send) + "\n\n"
    mailfile << "*" * 80 + "\n\n"
  end
end

mailfile.flush

if (system("/usr/sbin/sendmail #{DEST_EMAIL} < #{mailfile.path}"))
  puts "Handin successful for #{NAME}/#{CWID}."
else
  puts "Handin unsuccessful!"
end

mailfile.close
