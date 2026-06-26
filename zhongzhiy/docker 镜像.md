```sh
sudo mkdir -p /etc/docker
sudo tee /etc/docker/daemon.json <<EOF
{
  "registry-mirrors": [
    "https://docker.1ms.run",
    "https://dockerproxy.net",
    "https://proxy.vvvv.ee",
    "https://dockerproxy.link"
  ]
}
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker
```