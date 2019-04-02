
# TOPICS IN INTERNET RESEARCH (CS-678)

**Browser Crash Analysis on Low Memory Mobile Devices**

Abdul Manan [2020-10-0198]

M.Abrar Tariq [2020-10-0262]



## Introduction

According to statcounter, Android overtook Windows as world's most used operating system this year. This can easily be credited to the expansion of internet, driven primarily by the expansion of mobile broadband. However not everyone can afford a premium device, Low-End  devices  are  still  dominant  in  developing  countries.  The  issue  with  entry  level  phones  is that the user is bounded to limitedbyspecifications of the phone, so the apps may or may not run smoothly because of certain factors. Identification of those factors is the first step towards resolving  them.  In  case  of  a  browser,this  becomes  even  more  complicated  as  now  we  are dealing  with  a  dynamic  data-set.This  problem  is  crucial  for  prevention  of  entry  level  users from leaving the internet because of bad user experience.

## Goals

The objective of this project is to analyze several factors that lead to a browser crash on a low-end device. We will be targeting android followed by chrome as browser, our decision ismotivated  the  percentage  share  of  each  software  (Android  74.6%  and  Chrome56.34%).Specifically, the project will investigate the following:
  •Finding the main reasons behind the browser crashes on Low End devices.
  •Reproducingthose crashes underacontrolled environment.
  •Validatingthe enlisted reasons and measuringtheir input towards thebrowser crash.
  •Proposing a solution to resolve the problems that causes a browser to crash.
  
## Related Work

Google had announced recently an initiative to design customized OS and Application store for low end mobile devices in developing countries. Android Go is a whole new version of Google’s operating system designed specifically for those with low-end devices that don’t pack much RAM or processing power. It’s a lighter version of the Android OS and makes the system  more  optimized  for  devices  with  lower  performing  specs.  Google’s  VP  of  Project Management for Android and Google Play was quoted as saying last year, “I think that the data that we are seeing  from  industry analysts and what our manufacturing partners tell us  is that there are many,  many devices shipping -millions  of devices  shipping -every  year with 1 GB RAM and below". There is no other known related workin terms of browser crashes.The goal of this project is to investigate when memory crashes happen in a browser on such low memory devices and to design and implement solutions for avoiding and managing memory crashes.

## References

•http://admin.umt.edu.pk/Media/Site/icic/FileManager/Proceedings/Papers/42%20ICIC_2016_paper_42.pdf
•http://csl.snu.ac.kr/papers/tecs16.pdf•https://www.ibm.com/developerworks/linux/library/l-adfly/index.html
•https://www.ibm.com/developerworks/linux/library/l-adfly/index.html
•https://jawadmanzoor.files.wordpress.com/2012/01/android-report1.pdf
•https://www.it.iitb.ac.in/frg/wiki/images/f/f4/113050076_Rajesh_Prodduturi_Stage-01_report_8_113050076_stage01.pdf
•https://s2group.cs.vu.nl/wp-content/uploads/2017/12/greenlab_final_report.pdf
•https://ieeexplore.ieee.org/document/7346725
