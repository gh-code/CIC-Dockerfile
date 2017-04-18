# CentOS
FROM centos:6.8
MAINTAINER Gary Huang <gh.nctu+code@gmail.com>

RUN yum update -y
RUN yum groupinstall -y "X Window System"
RUN yum groupinstall -y "Development tools"

# Install LDAP, NFS, and AutoFS
RUN yum install -y authconfig openldap-clients nss-pam-ldapd nfs-utils autofs

# Configure LDAP
#RUN authconfig --enableldap --enableldapauth \
#       --ldapserver="" \
#       --ldapbasedn="" \
#       --update

# Configure NFS
RUN mkdir -p /usr/cad && \
    echo -e "synology_nas:/volume1/cad\t/usr/cad\tnfs\tdefaults\t0 0" >> /etc/fstab

# Configure AutoFS
ADD auto.syno /etc/
RUN chmod 700 /etc/auto.syno
RUN echo -e "/home\t\tprogram:/etc/auto.syno" >> /etc/auto.master

# Install shells and other dependencies
RUN yum install -y tcsh ksh \
    libXScrnSaver libXp glibc.i686 glibc-devel.i686 libstdc++-devel.i686 \
    libmng vim
RUN yum install -y python-pip

ENV CIC_USER root
ADD uname26 /root/
ADD run.sh /root/
RUN chmod 700 /root/run.sh
CMD /root/uname26 /root/run.sh
