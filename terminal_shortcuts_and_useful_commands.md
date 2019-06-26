##to display all info of all the topics with highlighted topic name

rostopic list | while read f; do echo $(tput setab 3)  $f $(tput sgr0) ; rostopic info $f; done
