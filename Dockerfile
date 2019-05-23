FROM nlknguyen/alpine-mpich

USER root

RUN apk update &&  \
    apk add openssh openrc && \
    rc-status && \
    touch /run/openrc/softlevel && \
    /etc/init.d/sshd start && \
    echo "PermitEmptyPasswords yes" >> /etc/ssh/sshd_config && \
    echo "ssh" >> /etc/securetty && \
    echo "12" > sudo passwd mpi --stdin && \
    echo "mpi:123" | sudo chpasswd

USER ${USER}

RUN ssh-keygen -t rsa -P "" -f /home/mpi/.ssh/id_rsa && \
    touch /home/mpi/.ssh/authorized_keys

ENTRYPOINT sudo service sshd restart && /bin/ash

#CMD ["/bin/ash"]
