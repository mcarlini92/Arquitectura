#!/bin/bash
scp $1 arquitectura@labdcc.fceia.unr.edu.ar:.
ssh arquitectura@labdcc.fceia.unr.edu.ar "scp $1 arquitectura@192.168.7.2:."
ssh -A -t arquitectura@labdcc.fceia.unr.edu.ar ssh -A arquitectura@192.168.7.2
