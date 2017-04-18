#/usr/bin/env bash
service rpcbind restart > /dev/null
service nslcd restart > /dev/null
service autofs restart > /dev/null
mount -a
/bin/tcsh -c "su - $CIC_USER"
