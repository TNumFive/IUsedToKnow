FROM ubuntu

# set apt non-interactive and only work in this scope
ARG DEBIAN_FRONTEND noninteractive

RUN apt update \
    && apt install -y systemd systemd-sysv locales\
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8 \
    && apt clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* 
    # remain the systemd related might make image larger but make it work much normally
    # && cd /lib/systemd/system/sysinit.target.wants/ \
    # && ls | grep -v systemd-tmpfiles-setup | xargs rm -f $1 \
    # && rm -f \
    # /etc/systemd/system/*.wants/* \
    # /lib/systemd/system/multi-user.target.wants/* \
    # /lib/systemd/system/local-fs.target.wants/* \
    # /lib/systemd/system/sockets.target.wants/*udev* \
    # /lib/systemd/system/sockets.target.wants/*initctl* \
    # /lib/systemd/system/basic.target.wants/* \
    # /lib/systemd/system/anaconda.target.wants/* \
    # /lib/systemd/system/plymouth* \
    # /lib/systemd/system/systemd-update-utmp*

# set locale cause the minimal-image doesn't
ENV LANG en_US.utf8
# for systemd-use
VOLUME [ "/sys/fs/cgroup" ]
# for large-amount of data if needed
VOLUME [ "/data" ]
# start with systemd as pid 1
CMD ["/lib/systemd/systemd"]

# make sure use docker run with `--privileged --volume /sys/fs/cgroup:/sys/fs/cgroup:ro`
# test with `docker run --rm --privileged --volume /sys/fs/cgroup:/sys/fs/cgroup:ro -itd ubuntu/systemd`
