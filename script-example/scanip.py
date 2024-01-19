from scapy.all import ARP, Ether, srp
import socket

def scan(ip):
    # IP Address for the destination
    # 'ip/24' indicates that we are scanning the entire subnet
    arp = ARP(pdst=ip)
    # MAC address to broadcast
    # ff:ff:ff:ff:ff:ff MAC address indicates broadcasting
    ether = Ether(dst="ff:ff:ff:ff:ff:ff")
    # Combine the ARP request with the Ethernet frame
    packet = ether/arp

    result = srp(packet, timeout=3, verbose=0)[0]

    # a list of clients, we will fill this in the upcoming loop
    clients = []

    for sent, received in result:
        # for each response, append ip and mac address to `clients` list
        clients.append({'ip': received.psrc, 'mac': received.hwsrc})

    return clients

# get my IP address
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("8.8.8.8", 80))
ip = s.getsockname()[0]
s.close()

# IP Address for the target
# Example: 192.168.1.1/24
target_ip = ip + "/24"
clients = scan(target_ip)

print("Available devices in the network:")
print("IP" + " "*18+"MAC")
for client in clients:
    print("{:16}    {}".format(client['ip'], client['mac']))
