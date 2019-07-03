import smtplib
import sys

server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
#Logs in to email id
server.login("bgsarcade@gmail.com", "GeneralKenobi!")
message = """\ 
Subject: Password Reset

Enter the code 4872
"""

recipient_email_id = sys.argv[1]

server.sendmail("bgsarcade@gmail.com", recipient_email_id, message)
server.quit()