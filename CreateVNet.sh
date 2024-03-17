
ip -all netns delete

ip netns add server
ip netns add client


ip link add name server-client type veth peer name client-server 

ip link set server-client netns server
ip link set client-server netns client


ip netns exec server ip addr add 192.168.1.1/24 dev server-client
ip netns exec server ip link set server-client up
ip netns exec server ethtool -K server-client rx off tx off
ip netns exec server ip route add default via 192.168.1.2



ip netns exec client ip addr add 192.168.1.2/24 dev client-server
ip netns exec client ip link set client-server up
ip netns exec client ethtool -K client-server rx off tx off
ip netns exec client ip route add default via 192.168.1.1


