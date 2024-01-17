import smtplib

def send_email(message):
    sender_email = 'REDACTED@gmail.com'
    receiver_email = 'REDACTED@gmail.com'
    password = 'REDACTED'
    server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
    server.login(sender_email,password)
    server.sendmail(sender_email,receiver_email,message)
    server.quit()

def main():
    message = 'Mission complete. Logs available locally.'
    send_email(message)

if __name__ == '__main__':
    main()
