#ifndef TCPSTANDARDMESSAGE_H
#define TCPSTANDARDMESSAGE_H


#include <string>
#include <vector>
#include <QSharedPointer>


namespace tcp_standard_message
{

enum MessageType
{
    invalid,
    setting,
    friends,
    groups,
};

enum UserSetting
{
    user_register,
    user_login,
    user_logout,
    change_password,
    rename_account,
    add_friends_label,
    remove_friends_label,
};

enum FriendOperation
{
    search_someone,
    add_friend,
    remove_friend,
    send_message,
    send_file,
    change_nickname,
    add_friend_to_group,
    invite_friend_to_group,
    recommend_friend,
};

enum GroupsOperation
{
    search_group,
    join_group,
    exit_group,
    create_group,
    dispersed_group,
    remove_someone_from_group,
    rename_group,
    set_group_join_attribute,
    change_group_master,
    disable_group_communication,
    enable_group_communication,
};


struct TCPMessage
{
    MessageType msg_typ;
    //如果msg_opt值为-1，表示信息请求失败(不存在的请求)
    int msg_opt;
    //这里的长度应包括字符'\0'
    uint32_t data_len;
    //该buff无论如何应有'\0'作为结束
    char *data_buf;
    TCPMessage();
    ~TCPMessage();
    TCPMessage(TCPMessage&& msg_stru);
    TCPMessage(const TCPMessage&) = delete;

    TCPMessage& operator=(const TCPMessage& msg_stru) = delete;
    //void operator=(const std::string& str);
    void copyDataFromString(const std::string& str);
    static QSharedPointer<TCPMessage> createTCPMessage(MessageType msg_typ, int msg_opt, const std::vector<std::string>& strs);
    static bool register_meta_object;
};



} // namespace tcp_standard_message


#endif // TCPSTANDARDMESSAGE_H
