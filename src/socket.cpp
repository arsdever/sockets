#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdexcept>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sockets/socket.hpp"

namespace ad::sockets
{

socket::socket() noexcept
    : _type(socket_type::undefined)
{
}

socket::~socket() noexcept { }

socket::socket(socket&& other) noexcept
    : _type(other._type)
{
    other._type = socket_type::undefined;
}

socket& socket::operator=(socket&& other) noexcept
{
    _type = other._type;
    other._type = socket_type::undefined;
    return *this;
}

void socket::bind(std::string_view address, uint16_t port) noexcept(false)
{
    throw std::runtime_error("Not implemented");
}

void socket::listen(int backlog) noexcept(false)
{
    throw std::runtime_error("Not implemented");
}

socket socket::accept() noexcept(false)
{
    throw std::runtime_error("Not implemented");
}

void socket::connect(std::string_view address, uint16_t port) noexcept(false)
{
    if (_type != socket_type::client)
        init(socket_type::client);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(address.data());

    if (::connect(_native, (sockaddr*)&addr, sizeof(addr)) == -1)
        throw std::runtime_error(strerror(errno));

    std::cout << "Connected" << std::endl;
}

void socket::close() noexcept { ::close(_native); }

void socket::send_all(const void* data, size_t size) noexcept(false)
{
    std::size_t bytes_transmitted =
        ::send(_native, data, size, 0);
    std::cout << "Bytes transmitted " << bytes_transmitted << " from actual "
              << size << std::endl;
}

void socket::recv_all(void* data, size_t size) noexcept(false)
{
    std::size_t bytes_received = ::recv(_native, data, size, 0);
    std::cout << "Bytes received " << bytes_received << std::endl;
}

void socket::init(socket_type type) noexcept(false)
{
    if (_type != socket_type::undefined)
        throw std::runtime_error("Socket already initialized");

    _type = type;
    _native = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_native == -1)
        throw std::runtime_error("Failed to create socket");
}

} // namespace ad::sockets
