cd ..
uname=builder
port=2222
if [ $# -gt 0 ]
  then
    args="$@"
fi

ssh $uname@clion_docker -p $port << EOL
  cd ~/Custom-Shell
  make $targets
EOL