# TrackerMon-Daemon
This is the implementation of a daemon which use services to monitoring system resources like: CPU usage, memory usage, synn_recv connection and critical errors
To run this project run the initTrackermon file
to generate errors manualy use commando on terminal: logger "message"
to generate a DDOS attack use hping3 hping3 -c 10000 -d 120 -S -w 64 -p 21 --flood --rand-source www.hping3testsite.com (https://www.blackmoreops.com/2015/04/21/denial-of-service-attack-dos-using-hping3-with-spoofed-ip-in-kali-linux/)
