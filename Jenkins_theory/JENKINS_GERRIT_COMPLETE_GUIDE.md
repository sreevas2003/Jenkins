# 📘 Android Build Automation Using Jenkins + Gerrit + GitHub Webhook

---

## 📌 1. Introduction

This document describes complete setup and practical implementation of:

- Jenkins CI/CD
- Jenkins Agent Setup
- Gerrit Code Review Integration
- Gerrit Trigger Build
- Git Webhook Trigger
- Merge Build Process
- Email Notifications
- End-to-End Validation

This documentation covers everything from initial setup to successful automated build.

---

# 🏗 2. Jenkins Theory

Jenkins is an open-source automation server used to automate build, test, and deployment processes.

### Key Concepts

- Master (Controller)
- Agent (Worker Node)
- Job
- Pipeline
- Plugin
- Webhook
- Trigger

### Jenkins Architecture

Master:
Controls scheduling and manages jobs.

Agent:
Executes build jobs.

Pipeline:
Scripted automation defined using Jenkinsfile.

---

# 🖥 3. Jenkins Installation (Ubuntu)

## Install Java

```bash
sudo apt update
sudo apt install openjdk-17-jdk -y
```

## Add Jenkins Repository

```bash
curl -fsSL https://pkg.jenkins.io/debian-stable/jenkins.io-2023.key | sudo tee \
/usr/share/keyrings/jenkins-keyring.asc > /dev/null

echo deb [signed-by=/usr/share/keyrings/jenkins-keyring.asc] \
https://pkg.jenkins.io/debian-stable binary/ | sudo tee \
/etc/apt/sources.list.d/jenkins.list > /dev/null
```

## Install Jenkins

```bash
sudo apt update
sudo apt install jenkins -y
sudo systemctl start jenkins
sudo systemctl enable jenkins
```

Access Jenkins:

```
http://<server-ip>:8080
```

Unlock Jenkins:

```bash
sudo cat /var/lib/jenkins/secrets/initialAdminPassword
```

---

# 🔗 4. Jenkins Agent Setup

1. Go to:
   Manage Jenkins → Nodes → New Node

2. Select:
   Permanent Agent

3. Configure:

```
Remote root directory: /home/jenkins
Launch method: SSH
```

4. Add SSH credentials.

5. Save and test connection.

---

# 🧑‍💻 5. Gerrit Theory

Gerrit is a web-based code review tool for Git.

### Features

- Code Review
- Patchset validation
- Trigger CI build
- Merge after approval

### Gerrit Workflow

Developer → Push to refs/for/master  
→ Gerrit Review  
→ Verified +1 (Jenkins)  
→ Code Review +2  
→ Merge  

---


# 🔌 6. Jenkins + Gerrit Integration

## Install Plugin

Manage Jenkins → Plugins → Install:

- Gerrit Trigger Plugin

## Configure Gerrit Server

Manage Jenkins → Configure System → Gerrit Trigger

Add:

```
Hostname: localhost
Port: 29418
Username: admin
```

Test connection.

---

# 🚀 7. Gerrit Trigger Build Setup

In Pipeline Job:

Build Triggers → Gerrit Event

Select events:

- Patchset Created
- Change Merged

---

# 📜 8. Jenkins Pipeline Example

```groovy
pipeline {
    agent { label 'remote-node' }

    options {
        timestamps()
        disableConcurrentBuilds()
    }

    environment {
        AOSP_DIR = "/home/sclabs/aosp_rpi"
    }

    stages {

        stage('Clean Workspace') {
            steps {
                cleanWs()
            }
        }

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build') {
            steps {
                sh '''
                cd $AOSP_DIR
                source build/envsetup.sh
                lunch rpi4-eng
                make -j8
                '''
            }
        }
    }

    post {
        success {
            echo "Build Successful"
        }
        failure {
            echo "Build Failed"
        }
    }
}
```

---

# 🔄 9. Merge Build Process

When code is approved in Gerrit:

Verified +1 → Code Review +2 → Submit

Gerrit merges into master branch.

Jenkins triggers build on:

Change Merged event.

---

# 🌐 10. GitHub Webhook Trigger

In GitHub:

Settings → Webhooks → Add Webhook

Payload URL:

```
http://<jenkins-ip>:8080/github-webhook/
```

Content Type:

```
application/json
```

In Jenkins:

Build Trigger → GitHub hook trigger

---

# 📧 11. Email Notification Setup

## Install Plugin

Email Extension Plugin

## Configure SMTP

Manage Jenkins → Configure System → Email Notification

Example (Gmail):

```
SMTP Server: smtp.gmail.com
Port: 587
Use TLS: Yes
```

## Pipeline Email Example

```groovy
post {
    success {
        emailext(
            subject: "Build Success: ${env.JOB_NAME}",
            body: "Build completed successfully.",
            to: "team@example.com"
        )
    }

    failure {
        emailext(
            subject: "Build Failed: ${env.JOB_NAME}",
            body: "Build failed. Check logs.",
            to: "team@example.com"
        )
    }
}
```

---

# 🧪 12. Practical Validation Steps

## Push Code to Gerrit

```bash
git add .
git commit -m "Test patch"
git push origin HEAD:refs/for/master
```

## Expected Flow

- Gerrit patch created
- Jenkins triggered automatically
- Verified +1 posted
- Approve and Merge
- Merge build triggered
- Email notification sent

---

# 🛠 13. Troubleshooting

## If build not triggered:

- Check Gerrit SSH connectivity
- Check plugin logs
- Verify event type selected

## If webhook not working:

- Check Jenkins logs
- Ensure URL is correct
- Check firewall

## If mail not sending:

- Check SMTP credentials
- Enable App password (Gmail)

---

# 🎯 14. Complete Flow Summary

Developer  
↓  
Gerrit  
↓  
Jenkins Trigger  
↓  
Agent Build  
↓  
Verification  
↓  
Merge  
↓  
Merge Build  
↓  
Email Notification  

---

# ✅ 15. Conclusion

We successfully implemented:

✔ Jenkins Installation  
✔ Agent Setup  
✔ Gerrit Integration  
✔ Gerrit Trigger Build  
✔ GitHub Webhook  
✔ Merge Build  
✔ Email Notifications  
✔ End-to-End Validation  

CI/CD pipeline is now fully automated.

---
