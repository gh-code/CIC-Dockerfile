# CIC-Dockerfile

The Dockerfile and some helper files make CIC tools working everywhere.

## Features
* Run CIC tools on Linux distributions not only CentOS 6
* Synology NAS and LDAP support

## Usage

1. Install Docker
2. Settings
    * Modify NFS server information in *main.cpp*
    ```c
    dflags += " --add-host=synology_nas:192.168.1.10";
    ```
    * If you have LDAP server, add information in *auto.syno* and *Dockerfile*
3. Build Docker image
    ```sh
    docker build -t cic .
    ```
4. Compile launcher program (*root* permission is required)
    ```sh
    $ g++ -o cic main.cpp
    $ chown root:root cic
    $ chmod u+s cic
    ```
5. Run
    ```sh
    $ ./cic <user>
    ```

## Copyright
Copyright (c) 2017 Gary Huang
