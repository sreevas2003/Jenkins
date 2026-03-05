# Jenkins Build Trigger Types

## Overview

Jenkins build triggers define **how and when a Jenkins job starts automatically**.
Triggers help automate builds based on events such as code commits, schedules, or external systems.

---

# 1. Manual Trigger

The build is started manually by the user.

Steps:

```
Jenkins Dashboard → Job → Build Now
```

Use case:

* Testing pipelines
* Running builds manually

---

# 2. Poll SCM Trigger

Jenkins periodically checks the source repository for changes.

Configuration:

```
Build Triggers → Poll SCM
```

Example schedule:

```id="gniv3z"
H/5 * * * *
```

Meaning:

* Jenkins checks the repository every **5 minutes**
* If changes are detected, the build starts

---

# 3. GitHub Webhook Trigger

GitHub sends a webhook event to Jenkins whenever code is pushed.

Configuration:

In Jenkins:

```
Build Triggers → GitHub hook trigger for GITScm polling
```

In GitHub:

```
Settings → Webhooks
```

Payload URL:

```id="vdd4ow"
http://<jenkins-ip>:8080/github-webhook/
```

Use case:

* Real-time CI builds from GitHub commits

---

# 4. Gerrit Trigger

Jenkins builds are triggered when a change is pushed to Gerrit.

Configuration:

```
Build Triggers → Gerrit event
```

Events:

* Patchset Created
* Change Merged
* Ref Updated

Use case:

* Code review based workflows
* Automated builds after Gerrit review submissions

---

# 5. Scheduled Build (Cron Trigger)

Build runs automatically based on a defined schedule.

Configuration:

```
Build Triggers → Build periodically
```

Example schedule:

```id="ggr4cb"
0 2 * * *
```

Meaning:

* Run the build every day at **2 AM**

Use case:

* Nightly builds
* Maintenance builds

---

# 6. Remote Trigger

Jenkins jobs can be triggered remotely using a URL.

Configuration:

```
Build Triggers → Trigger builds remotely
```

Example URL:

```id="v9xsl3"
http://<jenkins-ip>:8080/job/job-name/build?token=build-token
```

Use case:

* Trigger builds from external scripts or systems

---

# 7. Upstream Job Trigger

A job starts automatically when another Jenkins job completes.

Configuration:

```
Build Triggers → Build after other projects are built
```

Use case:

* Multi-stage pipelines
* Dependency builds

---

# 8. Pipeline Trigger

Pipelines can trigger other pipelines using Jenkins pipeline syntax.

Example:

```groovy id="dhcc0k"
build job: 'test-job'
```

Use case:

* Complex CI/CD workflows
* Multi-project builds

---

# Summary

| Trigger Type     | Purpose                          |
| ---------------- | -------------------------------- |
| Manual Trigger   | Start build manually             |
| Poll SCM         | Periodically check repository    |
| GitHub Webhook   | Trigger on GitHub push           |
| Gerrit Trigger   | Trigger on Gerrit review events  |
| Scheduled Build  | Run builds at specific times     |
| Remote Trigger   | Trigger build via URL            |
| Upstream Job     | Start build after another job    |
| Pipeline Trigger | Trigger job from pipeline script |

These triggers enable Jenkins to automatically build projects based on different events and workflows.
