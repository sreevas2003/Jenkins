# Jenkins Agent Setup Documentation (AOSP Build Node)

## 1. Overview

A Jenkins Agent (also called a **build node**) is a machine that performs build tasks assigned by the Jenkins Controller.
In this project setup, the Jenkins Controller runs on a separate machine, while the **Agent machine performs all build operations**, including Android Open Source Project (AOSP) incremental builds.

Key responsibilities of the agent:

* Execute Jenkins pipeline stages
* Perform AOSP builds
* Run Gerrit server
* Store generated build artifacts locally
* Provide build resources such as CPU, RAM, and disk

Architecture:

```text
Jenkins Controller
        │
        │ Trigger Jobs
        ▼
Jenkins Agent (agent-seenu)
        │
        ├── Gerrit Server
        ├── AOSP Source Tree
        └── Incremental Build Execution
```

---

# 2. System Requirements

| Component | Recommended                      |
| --------- | -------------------------------- |
| OS        | Ubuntu Linux                     |
| CPU       | 8 cores                          |
| RAM       | 16 GB                            |
| Disk      | 200 GB or more                   |
| Java      | OpenJDK 17                       |
| Git       | Latest version                   |
| Network   | SSH connectivity with controller |

Agent machine example configuration:

| Property             | Value                        |
| -------------------- | ---------------------------- |
| Hostname             | agent-seenu                  |
| Agent Root Directory | /home/sclabs/agent-seenu     |
| AOSP Source Path     | /home/sclabs/agent1/aosp_rpi |

---

# 3. Install Required Packages

Update package repository:

```bash
sudo apt update
```

Install required dependencies:

```bash
sudo apt install git openjdk-17-jdk curl wget -y
```

Verify Java installation:

```bash
java -version
```

---

# 4. Create Jenkins Agent Directory

Create the agent workspace directory:

```bash
mkdir -p /home/sclabs/agent-seenu
```

Set proper ownership if required:

```bash
sudo chown -R sclabs:sclabs /home/sclabs/agent-seenu
```

This directory will store:

* Jenkins workspace
* Build artifacts
* Temporary build files

---

# 5. Download Jenkins Agent JAR

On the Jenkins Controller:

1. Open Jenkins Dashboard
2. Navigate to:

```
Manage Jenkins → Nodes → New Node
```

Create a new node with the following settings:

| Field                 | Value                    |
| --------------------- | ------------------------ |
| Node Name             | agent-seenu              |
| Type                  | Permanent Agent          |
| Remote Root Directory | /home/sclabs/agent-seenu |
| Labels                | agent-seenu              |
| Launch Method         | Launch agent via SSH     |


---

# 6. Connect Agent to Jenkins Controller

After execution, the agent connects to the Jenkins controller and becomes **online**.

---

# 7. Verify Agent Connection

Check Jenkins dashboard:

```
Manage Jenkins → Nodes
```

The node **agent-seenu** should display:

```
Status: Online
```

Now Jenkins pipelines can run on this agent.

---

# 8. Agent Label Configuration

The Jenkins pipeline uses the following label to execute builds on the agent:

```text
agent-seenu
```

Pipeline example:

```groovy
pipeline {
    agent { label 'agent-seenu' }
}
```

This ensures all operations run on the agent machine.

---

# 9. Jenkins Workspace

Default Jenkins workspace location on the agent:

```text
/home/sclabs/agent-seenu/workspace
```

Workspace contains:

* Temporary build scripts
* Pipeline execution files
* Build logs

---

# 10. Security Considerations

To ensure secure communication:

* Use SSH authentication between Jenkins Controller and Agent
* Restrict user permissions
* Keep Java and Git updated
* Restrict Gerrit access to authorized users

---
  

---

# 11. Benefits of Using Jenkins Agent

* Offloads heavy build tasks from controller
* Allows scalable distributed builds
* Supports large projects like AOSP
* Improves build performance
* Enables isolated build environments

---
