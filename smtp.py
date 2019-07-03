import smtplib
import os

file = open("~/Desktop/BGS_Comp/BGS-Comp-Project/forgotPwdEmail.txt", 'r')

server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
#Logs in to email id
server.login("bgsarcade@gmail.com", "GeneralKenobi!")
message = """\
Subject: Password Reset

Enter the code 4872
"""

for line in file:
    recipient_email_id = str(line)
    recipient_email_id.rstrip('\n')
    break

server.sendmail("bgsarcade@gmail.com", recipient_email_id, message)
server.quit()
file.close()