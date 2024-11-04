cmake_minimum_required(VERSION 3.0)

project(socket_in_c)

add_executable(tcp_client tcp/tcp_client.c)
add_executable(tcp_server tcp/tcp_server.c)
add_executable(udp_client udp/udp_client.c)
add_executable(udp_server udp/udp_server.c)
