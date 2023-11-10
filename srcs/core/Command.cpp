#include "Command.hpp"
#include "utils.hpp"

Command::Command(std::string const &command, int32_t fd)
	: _command(command)
  , _user_fd(fd)
{
	logger(DEBUG, "got new command: " + command);
	return ;
}

int32_t Command::get_user_fd() const { return (this->_user_fd); }
std::string const &Command::get_command() const { return (this->_command); }

std::ostream	&operator<<(std::ostream &o, Command const &rhs)
{
	o
    << "fd:" << rhs.get_user_fd() << ", "
    << "command:" << rhs.get_command()
    << std::endl;
	return o;
}
