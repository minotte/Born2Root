# Boot2Root

> *A cybersecurity challenge focused on penetration testing, privilege escalation, and system enumeration.*

## 📖 Overview

**Boot2Root** is a security-oriented project that introduces the fundamentals of offensive cybersecurity through a vulnerable Linux server. The objective is to analyze, enumerate, and exploit the target machine in order to obtain **root privileges** using multiple independent attack paths.

Unlike traditional programming projects, Boot2Root emphasizes methodology, critical thinking, and understanding of operating systems, networking, and security mechanisms.

The challenge is performed on a provided virtual machine that must remain unmodified throughout the project.

---

## 🎯 Objectives

The main goals of this project are to:

* Perform network reconnaissance and service enumeration.
* Identify vulnerabilities and system misconfigurations.
* Exploit the target machine to gain an initial foothold.
* Escalate privileges until obtaining a root shell.
* Discover at least **two different exploitation paths** leading to root access.
* Document every step in detailed technical write-ups.

---

## 🛠️ Skills Developed

Throughout this project, the following areas are explored:

* Linux system administration
* Networking fundamentals
* Service enumeration
* Vulnerability assessment
* Privilege escalation
* Web security
* Authentication mechanisms
* Shell environments
* Technical documentation
* Penetration testing methodology

---

## 📂 Project Structure

The repository typically contains:

```text
.
├── writeup1
├── writeup2
├── scripts/
└── bonus/
```

* **writeup1** – Documentation for the first exploitation method.
* **writeup2** – Documentation for the second exploitation method.
* **scripts/** – Optional helper scripts used during the assessment (no binaries).
* **bonus/** – Additional exploitation paths discovered beyond the mandatory requirements.

---

## 📋 Requirements

* Use the provided **64-bit virtual machine**.
* Do **not** modify the ISO image.
* Do **not** exploit the bootloader (GRUB) or alter the virtual disk offline.
* All attacks must target the **running server**.
* Brute-force attacks are prohibited.
* Every exploitation method must be fully understood and documented.

---

## 📚 Learning Outcomes

By completing this project, students gain practical experience with:

* Real-world penetration testing workflows
* Information gathering and reconnaissance
* Exploitation techniques
* Linux privilege escalation
* Security analysis
* Writing professional penetration testing reports

---

## Virtual Machine

```bash
wget https://cdn.intra.42.fr/isos/BornToSecHackMe-v1.1.iso
```

```sh
#!/bin/bash

VBOX="/path/VBoxManage.exe"
ISO="/path/BornToSecHackMe-v1.1.iso"
VM_NAME="BornToRoot"
RAM=512
DISK_SIZE=8192  

"$VBOX" createvm --name "$VM_NAME" --ostype "Debian_64" --register
"$VBOX" modifyvm "$VM_NAME" --memory $RAM --ioapic on
"$VBOX" modifyvm "$VM_NAME" --nic1 bridged --bridgeadapter1 "WiFi"
"$VBOX" createhd --filename "BornToRoot.vdi" --size $DISK_SIZE
"$VBOX" storagectl "$VM_NAME" --name "SATA" --add sata --controller IntelAhci
"$VBOX" storageattach "$VM_NAME" ...
"$VBOX" startvm "$VM_NAME"
```
----
## Requierement


| software | description | cmd install |
|---|----|----|
| gobuster | tool for brute forcing directories on web servers |```sudo apt install gobuster```|
| nmap | network scanner |```sudo apt install nmap```|

---

## ⚠️ Disclaimer

This repository is intended for **educational purposes only**.

All techniques and tools should only be used in controlled environments or systems for which you have explicit authorization.


## REF

https://www.youtube.com/watch?v=LkcdN7hZOuM 



https://launchpad.net/ubuntu/+source/mysql-5.5/5.5.44-0ubuntu0.12.04.1