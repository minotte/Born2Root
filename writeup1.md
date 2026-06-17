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