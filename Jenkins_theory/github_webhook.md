# GitHub Webhook Trigger Setup (Simple Guide)

## Overview

A GitHub Webhook automatically triggers a Jenkins build whenever code is pushed to a GitHub repository.
This allows continuous integration where Jenkins builds the project immediately after a code change.

---

# 1. Configure Webhook in GitHub

Open your GitHub repository.

Navigate to:

```
Settings → Webhooks → Add Webhook
```

Fill in the following details.

### Payload URL

```
http://<jenkins-ip>:8080/github-webhook/
```

Example:

```
http://192.168.1.10:8080/github-webhook/
```

### Content Type

```
application/json
```

### Events

Select:

```
Just the push event
```

Click **Add Webhook**.

---

# 2. Install Required Jenkins Plugin

Open Jenkins dashboard.

Navigate to:

```
Manage Jenkins → Plugin Manager
```

Install the plugin:

```
GitHub Integration Plugin
```

Restart Jenkins if required.

---

# 3. Configure Jenkins Job

Open your Jenkins job.

Go to:

```
Configure → Build Triggers
```

Enable:

```
GitHub hook trigger for GITScm polling
```

Save the configuration.

---

# 4. Configure Git Repository in Jenkins

Inside the Jenkins job configuration, add the Git repository URL.

Example:

```
https://github.com/username/project-name.git
```

If authentication is required, configure Git credentials in Jenkins.

---

# 5. Test Webhook Trigger

Make a change in the GitHub repository and push the code:

```bash
git add .
git commit -m "Test webhook trigger"
git push origin main
```

GitHub sends a webhook event to Jenkins.

Jenkins automatically starts the build.

---

# 6. Verify Webhook Delivery

In GitHub repository:

```
Settings → Webhooks → Recent Deliveries
```

Check if the webhook request returned:

```
Status: 200 OK
```

This confirms that Jenkins received the event successfully.

---

# Workflow

```
Developer pushes code to GitHub
        │
        ▼
GitHub Webhook sends event
        │
        ▼
Jenkins receives webhook
        │
        ▼
Jenkins job starts automatically
        │
        ▼
Build executed
```

---

# Summary

Steps to enable GitHub webhook trigger:

1. Add webhook in GitHub repository
2. Install GitHub integration plugin in Jenkins
3. Enable GitHub hook trigger in Jenkins job
4. Push code to trigger automatic build

This enables automatic CI builds whenever code is pushed to GitHub.
