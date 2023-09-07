ucp_sms_msg:	main.cpp ucp_sms_msg.cpp ucp_sms_msg.hpp
	g++ -Wall -Wextra -Wpedantic -Weffc++ -Wfloat-equal -Wshadow -Wcast-align -Wswitch-default -Winit-self -Wredundant-decls -O3 -DNDEBUG -o $@ $^


.PHONY: clean
clean:
	rm -rf ucp_sms_msg

