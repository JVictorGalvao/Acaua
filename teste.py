 import urllib.request  
 import json  

     url = 'http://tools.fifaguide.com/api/topten/pace'  
 resp = urllib.request.urlopen(url+str()).read()  
 resp = json.loads(resp.decode('utf-8'))
  
  for x in resp:  
   print(x['first_name']+' '+x['last_name'])  
   print('Rating:'+x['rating'])  
   print("") 