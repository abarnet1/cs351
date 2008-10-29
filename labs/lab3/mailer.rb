#! /usr/local/bin/ruby

require 'rubygems'
require 'actionmailer'
require 'activesupport'

SMTP_HOST   = 'localhost'
SMTP_PORT   = 25
SMTP_DOMAIN = 'host220.cns.iit.edu'
DEST_EMAIL  = 'lee@iit.edu'
FROM_EMAIL  = 'cs351@host220.cns.iit.edu'
COURSE_ID   = 'CS 351'
LAB_NAME    = 'malloclab'

ActionMailer::Base.delivery_method = :smtp
ActionMailer::Base.smtp_settings = { 
  :address => SMTP_HOST,
  :port    => SMTP_PORT,
  :domain  => SMTP_DOMAIN
}

class Mailer < ActionMailer::Base
  def lab_handin(dest, sender, subj, body, files)
    recipients      dest
    from            sender
    subject         subj
    body            body

    files.each do |file| 
      if !(File.exists?(file) and File.readable?(file))
        puts "Can't read or locate file: #{file}"
        exit
      else
        puts "Sending #{File.basename(file)}, last modified #{File.mtime(file)}..."
        attachment :content_type => "text/plain", 
                   :body         => File.read(file),
                   :filename     => file.gsub(/.*\//, '')
      end
    end
  end
end

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

  subject = "#{COURSE_ID} #{LAB_NAME} submission for #{team.to_sentence}"

  mail_text = "Lab submission for:\n\t#{team[0].name} / #{team[0].cwid}\n"
  for i in 1...team.length
    mail_text += "\t#{team[i].name} / #{team[i].cwid}\n"
  end

  begin
    Mailer.deliver_lab_handin(DEST_EMAIL, FROM_EMAIL, subject, mail_text, ARGV)
    puts "Submission successful for #{team.to_sentence}"
  rescue Exception => e
    puts "Error sending mail: #{e}"
    exit
  end
end
