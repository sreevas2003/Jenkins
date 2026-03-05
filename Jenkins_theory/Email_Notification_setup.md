# Jenkins Email Notification Setup (Simple Guide)

## Overview

Email notifications in Jenkins are used to inform users about build results.
In this project, Jenkins sends an email when the AOSP build **succeeds or fails**.

Recipient email:

```
sreevas2003@gmail.com
```

---

# 1. Install Mail Plugin

Open Jenkins Dashboard and go to:

```
Manage Jenkins → Plugin Manager
```

Install the plugin:

```
Email Extension Plugin
```

Restart Jenkins if required.

---

# 2. Configure SMTP Server

Go to:

```
Manage Jenkins → Configure System
```

Scroll to **E-mail Notification** section.

Fill the following details (example using Gmail):

| Field                   | Value                                               |
| ----------------------- | --------------------------------------------------- |
| SMTP Server             | smtp.gmail.com                                      |
| Use SMTP Authentication | ✔                                                   |
| Username                | [your_email@gmail.com](mailto:your_email@gmail.com) |
| Password                | Gmail App Password                                  |
| Use SSL                 | ✔                                                   |
| SMTP Port               | 465                                                 |

Save the configuration.

---

# 3. Test Email Configuration

In the same section click:

```
Test configuration by sending test e-mail
```

Enter recipient:

```
sreevas2003@gmail.com
```

Click **Test configuration**.

If successful, Jenkins will send a test email.

---

# 4. Add Email Notification in Pipeline

Add email notification inside the Jenkins pipeline.

Example:

```groovy
post {

    success {
        mail to: 'sreevas2003@gmail.com',
        subject: "Build SUCCESS - ${env.JOB_NAME} #${env.BUILD_NUMBER}",
        body: "The AOSP build completed successfully."
    }

    failure {
        mail to: 'sreevas2003@gmail.com',
        subject: "Build FAILED - ${env.JOB_NAME} #${env.BUILD_NUMBER}",
        body: "The AOSP build failed. Please check Jenkins logs."
    }

}
```

---

# 5. Email Notification Workflow

```
Code Push to Gerrit
        │
        ▼
Jenkins Build Triggered
        │
        ▼
Build Success / Failure
        │
        ▼
Email Sent to Developer
```

---

# Summary

Steps to enable email notification:

1. Install Email Extension Plugin
2. Configure SMTP settings in Jenkins
3. Test email configuration
4. Add mail step in Jenkins pipeline

After configuration, Jenkins will automatically send email notifications for every build result.
