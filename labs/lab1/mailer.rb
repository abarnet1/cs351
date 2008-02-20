#! /usr/bin/env ruby

require 'net/smtp'
require 'rubygems'
require 'mailfactory'

SMTP_HOST  = 'localhost'
SMTP_PORT  = 25
DEST_EMAIL = 'lee@iit.edu'
FROM_EMAIL = 'cs351@host220.cns.iit.edu'
COURSE_ID  = 'CS 351'
LAB_NAME   = 'clab'

class Student 
  attr_accessor :name, :cwid
  def to_s
    @name
  end
end

def read_team
  team = []
  loop do
    member = Student.new
    print "Submitter name: "
    member.name = $stdin.gets.chomp
    print "Submitter CWID: "
    member.cwid = $stdin.gets.chomp
    team << member
  
    print "More team members? (y/N): "
    break unless $stdin.gets.downcase =~ /y/
  end
  return team
end

if $0 == __FILE__
  if ARGV.length < 1
    puts "No attachments specified.  Submission aborted."
    exit
  end

  mail = MailFactory.new
  mail.to = DEST_EMAIL
  mail.from = FROM_EMAIL

  team = []
  loop do
    puts "\nEnter team information:"
    team = read_team

    if team.size > 2
      puts "\nWarning: too many team members!"
    end

    puts "\nSubmitting for:"
    team.each do |member|
      puts "\t#{member.name} / #{member.cwid}"
    end
    
    print "Continue? (Y/n): "
    
    break unless $stdin.gets.downcase =~ /n/
  end

  pretty_names = team.inject {|anded, n| "#{anded} and #{n}"}
  mail.subject = "#{COURSE_ID} #{LAB_NAME} submission for #{pretty_names}"
  
  mail_text = "Lab submission for:\n\t#{team[0].name} / #{team[0].cwid}\n"
  for i in 1...team.length
    mail_text += "\t#{team[i].name} / #{team[i].cwid}\n"
  end
  mail.text = mail_text

  puts
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
    Net::SMTP.start(SMTP_HOST, SMTP_PORT) do |smtp|
      smtp.send_message(mail.to_s(), mail.from.first, mail.to.first)
    end
    puts "Submission successful for #{pretty_names}"
  rescue Exception => e
    puts "Error sending mail: #{e}"
    exit
  end
end
