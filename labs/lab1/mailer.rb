#! /usr/bin/env ruby

### Set the following two variables to your own full name(s) and 8 digit CWID(s) ###
### If you aren't working in a group, remove the second name/CWID                ###

NAME = [ "John Doe", "Jane Adams"]
CWID = [ 12345678,   34567890   ]

##############################################################################

### Don't touch anything below this line! #################################### 

require 'net/smtp'
require 'rubygems'
require 'mailfactory'

DEST_EMAIL = 'lee@iit.edu'
COURSE_ID  = 'CS 351'
LAB_NAME   = 'clab'

if ARGV.length < 1
  puts "No attachments specified.  Submission aborted."
  exit
end

mail = MailFactory.new
mail.to = DEST_EMAIL
mail.from = "cs351@host220.cns.iit.edu"

if NAME.size != CWID.size
  puts "Number of names must match the number of CWIDs!"
  exit
else
  if NAME[0] =~ /John Doe/ and CWID[0] == 12345678
    puts "Change your name(s)/cwid(s) in the #{$0} script before submitting!"
    exit
  end
  pretty_names = NAME[0]
  mail_text = "Lab submission for:\n\t#{NAME[0]} / #{CWID[0]}\n"
  for i in 1...NAME.length
    pretty_names += " and #{NAME[i]}"
    mail_text += "\t#{NAME[i]} / #{CWID[i]}\n"
  end
  mail.subject = "#{COURSE_ID} #{LAB_NAME} submission for #{pretty_names}"
  mail.text = mail_text
end

ARGV.each do |to_send| 
  if !(File.exists?(to_send) and File.readable?(to_send))
    puts "Can't read or locate file: #{to_send}"
    exit
  else
    puts "Sending #{File.basename(to_send)}, last modified #{File.mtime(to_send)}..."
    mail.attach(to_send)
  end
end

begin
  Net::SMTP.start('localhost', 25) do |smtp|
    smtp.send_message(mail.to_s(), mail.from.first, mail.to.first)
  end
  puts "Submission successful for #{pretty_names}"
rescue Exception => e
  puts "Error sending mail: #{e}"
  exit
end
