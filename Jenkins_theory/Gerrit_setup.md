# Gerrit Server Setup and Integration with Jenkins for AOSP Incremental Builds

## 1. Overview

Gerrit is a web-based Git code review system used to review and manage code changes before merging them into the main branch.

In this setup:

* Gerrit runs on the **Agent machine**
* Jenkins controller triggers builds
* Jenkins agent performs **AOSP incremental builds**
* Developers push code changes to Gerrit
* Gerrit automatically triggers Jenkins builds

### Architecture

```
Developer
   │
   │ git push
   ▼
Gerrit Server
(172.16.0.88:8090)
   │
   │ Gerrit Event
   ▼
Jenkins Controller
   │
   ▼
Jenkins Agent (agent-seenu)
   │
   ▼
AOSP Incremental Build
```

---

# 2. System Requirements

| Component | Value              |
| --------- | ------------------ |
| OS        | Ubuntu Linux       |
| Java      | OpenJDK 17         |
| Git       | Latest Version     |
| SSH       | Enabled            |
| RAM       | Minimum 8 GB       |
| Disk      | 200 GB recommended |

### Ports Used

| Service       | Port  |
| ------------- | ----- |
| Gerrit Web UI | 8090  |
| Gerrit SSH    | 29419 |

Server IP:

```
172.16.0.88
```

---

# 3. Install Required Packages

Update package lists and install dependencies.

```bash
sudo apt update
sudo apt install git openjdk-17-jdk -y
```

Verify Java installation:

```bash
java -version
```

---

# 4. Download Gerrit

Download the Gerrit WAR file:

```bash
wget https://gerrit-releases.storage.googleapis.com/gerrit-3.13.3.war
```

---

# 5. Initialize Gerrit Site

Create the Gerrit working directory:

```bash
mkdir gerrit_review
cd gerrit_review
```

Initialize Gerrit:

```bash
java -jar gerrit-3.13.3.war init -d .
```

During initialization configure:

| Setting        | Value                          |
| -------------- | ------------------------------ |
| Authentication | DEVELOPMENT_BECOME_ANY_ACCOUNT |
| HTTP Port      | 8090                           |
| SSH Port       | 29419                          |
| Git storage    | default                        |

---

# 6. Start Gerrit Server

Start Gerrit service:

```bash
./bin/gerrit.sh start
```

Check service status:

```bash
./bin/gerrit.sh status
```

---

# 7. Access Gerrit Web Interface

Open a browser and access:

```
http://172.16.0.88:8090
```

Login using the admin account.

---

# 8. Create Gerrit Project

Create a new project using SSH:

```bash
ssh -p 29419 admin@172.16.0.88 gerrit create-project frameworks_base
```

Repository structure inside Gerrit:

```
gerrit_review/
 └── git/
      ├── All-Projects.git
      ├── All-Users.git
      └── frameworks_base.git
```

---

# 9. Configure Local AOSP Repository

Navigate to the AOSP frameworks module:

```bash
cd /home/sclabs/agent1/aosp_rpi/frameworks/base
```

Add Gerrit as a remote repository:

```bash
git remote add gerrit ssh://admin@172.16.0.88:29419/frameworks_base
```

Verify remote configuration:

```bash
git remote -v
```

---

# 10. Push Initial Code to Gerrit

Push the existing project history to Gerrit:

```bash
git push gerrit HEAD:master
```

This uploads the complete history of the framework module.

---

# 11. Install Gerrit Commit Hook

Gerrit requires a **Change-Id** in every commit message.

Install the commit-msg hook:

```bash
gitdir=$(git rev-parse --git-dir)
scp -p -P 29419 admin@172.16.0.88:hooks/commit-msg ${gitdir}/hooks/
chmod +x ${gitdir}/hooks/commit-msg
```

---

# 12. Push Code for Review

After modifying source files:

```bash
git add .
git commit -m "Framework modification"
```

Push the change to Gerrit for review:

```bash
git push gerrit HEAD:refs/for/master
```

Gerrit creates a review change.

Example review URL:

```
http://172.16.0.88:8090/c/frameworks_base/+/161
```

---

# 13. Gerrit Event Trigger

When a patchset is created:

```
Patchset Created
```

Gerrit sends an event to Jenkins.

Jenkins automatically starts a build using the Gerrit Trigger plugin.

---

# 14. Incremental Build Process

Pipeline steps:

1. Reset workspace
2. Fetch Gerrit patchset
3. Apply patch using cherry-pick
4. Perform incremental AOSP build

Build commands:

```bash
source build/envsetup.sh
lunch aosp_rpi4-bp1a-userdebug
make -j6
```

# 18. Complete Workflow

```
Developer modifies framework
        │
        ▼
git push gerrit HEAD:refs/for/master
        │
        ▼
Gerrit creates review
        │
        ▼
Jenkins triggered
        │
        ▼
Fetch patchset
        │
        ▼
Incremental AOSP build
        │
        ▼
Image copied to agent folder
        │
        ▼
Email notification sent
```
