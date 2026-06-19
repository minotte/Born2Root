# Writeup1

first way to become root

## netcat

```bash
nmap -sn 192.168.1.0/24 -oA scan.txt
nmap -p- 192.168.1.146
>> Starting Nmap 7.94SVN ( https://nmap.org ) at 2026-06-16 16:21 CEST
>> Nmap scan report for BornToSecHackMe.lan (192.168.1.146)
>> Host is up (0.047s latency).
>> Not shown: 65529 closed tcp ports (conn-refused)
>> PORT    STATE SERVICE
>> 21/tcp  open  ftp
>> 22/tcp  open  ssh
>> 80/tcp  open  http
>> 143/tcp open  imap
>> 443/tcp open  https
>> 993/tcp open  imaps
```
---

| Port	  | Service	| mean |
| ----- | ----- | ----- | 
| 21/tcp | 	FTP | File trqnsfert Protocol |
| 22/tcp | 	SSH | shell connection  |
| 80/tcp | 	HTTP | website  http://192.168.1.X |
| 143/tcp | IMAP |  email Server |
| 443/tcp | HTTPS | website SSL |
| 993/tcp | IMAPS | IMAP chiffré  |
---

## wesite

![alt](./img/website.png)

```html
<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<title>Hack me if you can</title>
	<meta name='description' content='Simple and clean HTML coming soon / under construction page'/>
	<meta name='keywords' content='coming soon, html, html5, css3, css, under construction'/>	
	<link rel="stylesheet" href="style.css" type="text/css" media="screen, projection" />
	<link href='http://fonts.googleapis.com/css?family=Coustard' rel='stylesheet' type='text/css'>

</head>
<body>
	<div id="wrapper">
		<h1>Hack me</h1>
		<h2>We're Coming Soon</h2>
		<p>We're wetting our shirts to launch the website.<br />
		In the mean time, you can connect with us trought</p>
		<p><a href="https://fr-fr.facebook.com/42Born2Code"><img src="fb.png" alt="Facebook" /></a> <a href="https://plus.google.com/+42Frborn2code"><img src="+.png" alt="Google +" /></a> <a href="https://twitter.com/42born2code"><img src="twitter.png" alt="Twitter" /></a></p>
	</div>
</body>
</html>
```

---- 

### gobuster

```bash
gobuster dir -u https://192.168.1.64/ -w common.txt -k -x php,bak,txt,sql      

===============================================================
Gobuster v3.6
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@firefart)
===============================================================
[+] Url:                     https://192.168.1.64/
[+] Method:                  GET
[+] Threads:                 10
[+] Wordlist:                common.txt
[+] Negative Status codes:   404
[+] User Agent:              gobuster/3.6
[+] Extensions:              php,bak,txt,sql
[+] Timeout:                 10s
===============================================================
Starting gobuster in directory enumeration mode
===============================================================
/index.html           (Status: 200) [Size: 1025]
/.html                (Status: 403) [Size: 286]
/forum                (Status: 403) [Size: 286]
/fonts                (Status: 301) [Size: 314] [--> http://192.168.1.X/fonts/]
/.html                (Status: 403) [Size: 286]
/forum/index.php?mode=lmezard.sql (Status: 200) [Size: 5317]
/forum/index.php?mode=lmezard.php (Status: 200) [Size: 5317]
/forum/index.php?mode=login.bak (Status: 200) [Size: 5317]
/forum/index.php?mode=lmezard.bak (Status: 200) [Size: 5317]
/forum/index.php?mode=lmezard (Status: 200) [Size: 5317]
/forum/index.php?mode=login.php (Status: 200) [Size: 5317]
/forum/index.php?mode=login.sql (Status: 200) [Size: 5317]
/forum/index.php?mode=login (Status: 200) [Size: 3270]
/forum/index.php?mode=login.txt (Status: 200) [Size: 5317]
/forum/index.php?mode=lmezard.txt (Status: 200) [Size: 5317]
/forum/index.php?mode=qudevide (Status: 200) [Size: 5317]
/forum/index.php?mode=qudevide.bak (Status: 200) [Size: 5317]
/forum/index.php?mode=qudevide.txt (Status: 200) [Size: 5317]
/forum/index.php?mode=qudevide.php (Status: 200) [Size: 5317]
/forum/index.php?mode=qudevide.sql (Status: 200) [Size: 5317]
/forum/index.php?mode=thor.txt (Status: 200) [Size: 5317]
/forum/index.php?mode=thor (Status: 200) [Size: 5317]
/forum/index.php?mode=thor.php (Status: 200) [Size: 5317]
/forum/index.php?mode=thor.bak (Status: 200) [Size: 5317]
/forum/index.php?mode=thor.sql (Status: 200) [Size: 5317]
/forum/index.php?mode=wandre (Status: 200) [Size: 5317]
/forum/index.php?mode=wandre.sql (Status: 200) [Size: 5317]
/forum/index.php?mode=wandre.php (Status: 200) [Size: 5317]
/forum/index.php?mode=wandre.bak (Status: 200) [Size: 5317]
/forum/index.php?mode=wandre.txt (Status: 200) [Size: 5317]
/forum/index.php?mode=zaz (Status: 200) [Size: 5317]
/forum/index.php?mode=zaz.txt (Status: 200) [Size: 5317]
/forum/index.php?mode=zaz.php (Status: 200) [Size: 5317]
/forum/index.php?mode=zaz.sql (Status: 200) [Size: 5317]
/forum/index.php?mode=zaz.bak (Status: 200) [Size: 5317]
/forum/index.php      (Status: 200) [Size: 5288]
/cgi-bin/             (Status: 403) [Size: 289]
/forum                (Status: 301) [Size: 314] [--> https://192.168.1.64/forum/]
/phpmyadmin           (Status: 301) [Size: 319] [--> https://192.168.1.64/phpmyadmin/]
/server-status        (Status: 403) [Size: 294]
/webmail              (Status: 301) [Size: 316] [--> https://192.168.1.64/webmail/]
Progress: 23100 / 23105 (99.98%)
===============================================================
Finished
===============================================================
```

## https://ip/forum

> ![Warning]
> to connect at forum don't use http:// is forbidden use https://

![alt](/img/forum.png)

When we check the topics, our eyes are attract by "Problem login ?" 

### Problem login ?

that look likes a copy of a pcap file. we can someone (lmezard) trying to become admin and root. The user wanted to show a failled but the user make a mistake and leak his password.
``Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Failed password for invalid user !q\]Ej?*5K5cy*AJ from 161.202.39.38 port 57764 ssh2``

So we use this information to log in. **lmezard** and `!q\]Ej?*5K5cy*AJ`
![alt](./img/login.png)
That works, we can find the [email](#users-informations).

Now go to:


## https://ip/webmail

![alt](img/webmail_log.png)

let's try to connect with the email laurie@borntosec.net and the same password **!q\]Ej?*5K5cy*AJ** , lot of person doesn't change their password between the differents applications. 

We can see an email with the subject ***DB Access***

![alt](img/mail.png)

let's connect at the database with this informationm user = **root** pwd = ``Fg-'kKXBj87E:aJ$``.

## https://ip/phpmyadmin

We can update our [users informations](#users-informations) with this  localhost->forum_db->mlf2_userdata

there is *user_pw*, we try to decrypt the password of lmezard because we now the **clear pwd** but we didn't found. On ``https://192.168.1.146/forum/index.php?mode=user&action=edit_profile`` we can modifie the password, that change in the DB but not for the webmail service.

So we know the clear pwd of laurie so we can copy from the DB and paste in the pwd of **admin**

Now we can connect in the forum with **admin** and the same password than **lmezzard** 

## Users informations

|   Username |	Type | UID |	Homepage	| E-mail | pwd |
|----| ---- | --- | --- |----- | ---- | 
|   root |	root |	 0  | |	root@mail.borntosec.net| Fg-'kKXBj87E:aJ$|
|   admin |	Admin |	 1000  | |	admin@borntosec.net | |
|   lmezard |	User | 1040| 	 |		laurie@borntosec.net  | !q\]Ej?*5K5cy*AJ |
|   qudevide |	User | | 	 |	qudevide@borntosec.net  | |
|   thor |	User |	 | | 	thor@borntosec.net  | |
|   wandre |	User | | 	 | wandre@borntosec.net | |
|   zaz |	User |	 | | zaz@borntosec.net | |







https://192.168.1.146/forum/index.php

"In order to log in, cookies have to be activated!"

 Modifier	Modifier Éditer en place	Copier Copier	Effacer Effacer	1	2	admin		0	0000-00-00	ed0fd64f25f3bd3a54f8d272ba93b6e76ce7f3d0516d551c28	admin@borntosec.net	1					8	2015-10-08 23:08:16	2015-10-08 23:08:16	192.168.1.47	2015-10-08 01:47:03	NULL	0	0	1	0	0	0	0	0						0		2,5,3,1,6,4
	Modifier Modifier	Modifier Éditer en place	Copier Copier	Effacer Effacer	2	0	qudevide		0	0000-00-00	a12e059d6f4c21c6c5586283c8ecb2b65618ed0a0dc1b302a2	qudevide@borntosec.net	0					1	2015-10-08 02:01:43	2015-10-08 02:02:05	192.168.1.47	2015-10-08 01:52:42	NULL	0	0	1	0	0	0	0	0						0		1,2,3,4
	Modifier Modifier	Modifier Éditer en place	Copier Copier	Effacer Effacer	3	0	thor		0	0000-00-00	d30668b779542d60c4cde29e7170148198b1623f4453866797	thor@borntosec.net	0					1	2015-10-08 01:58:15	2015-10-08 01:58:41	192.168.1.47	2015-10-08 01:53:16	NULL	0	0	1	0	0	0	0	0						0		1,2,3
	Modifier Modifier	Modifier Éditer en place	Copier Copier	Effacer Effacer	4	0	wandre		0	0000-00-00	f8562b53084d60efa4208fa50d1ef753ef18e089d2dd56c4ed	wandre@borntosec.net	0					1	2015-10-08 01:57:38	2015-10-08 01:58:03	192.168.1.47	2015-10-08 01:53:48	NULL	0	0	1	0	0	0	0	0						0		1,2
	Modifier Modifier	Modifier Éditer en place	Copier Copier	Effacer Effacer	5	0	lmezard		0	0000-00-00	0171e7dbcbf4bd21a732fa859ea98a2950b4f8aa1e5365dc90	laurie@borntosec.net	0					5	2026-06-18 15:34:09	2026-06-18 15:34:09	192.168.1.144	2015-10-08 01:54:38	NULL	0	0	1	0	0	0	0	0						0		8,7,5,4,3,2,6,1
	Modifier Modifier	Modifier Éditer en place	Copier Copier	Effacer Effacer	6	0	zaz		0	0000-00-00	f10b3271bf523f12ebd58ef8581c851991bf0d4b4c4bf49d7c	zaz@borntosec.net	0	