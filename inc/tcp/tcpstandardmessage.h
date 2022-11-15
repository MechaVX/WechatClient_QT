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
    //指客户端主动刷新消息
    flush,
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
    agree_add_friend,
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
    agree_join_group,
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

enum FlushOperation
{
    flush_message,
    flush_friends,
    flush_group,
};


#define ACCOUNT_LEN 11

struct TCPMessage
{
    //定义服务器
    static const QString server_account;
    quint32 timestamp;
    MessageType msg_typ;
    //如果msg_opt值为-1，表示信息请求失败(不存在的请求)
    int msg_opt;
    //发送者账号，或手机号，末位用'\0'填充
    char sender[ACCOUNT_LEN + 1];
    //receiver一般为服务器、用户、群号，末位用'\0'填充
    char receiver[ACCOUNT_LEN + 1];
    //这里的长度应包括字符'\0'
    quint32 data_len;
    //除非data_len=0时data_buf为nullptr，否则该buff无论如何应有'\0'作为结束
    char *data_buf;
    TCPMessage();
    ~TCPMessage();
    TCPMessage(TCPMessage&& msg_stru);
    TCPMessage(const TCPMessage&) = delete;
    TCPMessage& operator=(const TCPMessage& other) = delete;
    //void operator=(const std::string& str);
    void copyDataFromString(const std::string& str);
    //static QSharedPointer<TCPMessage> createTCPMessage(MessageType msg_typ, int msg_opt, const std::vector<std::string>& strs);
    //
    static QSharedPointer<TCPMessage> createTCPMessage(
                MessageType msg_typ,
                int msg_opt,
                const QString& sender,
                const QString& receiver = TCPMessage::server_account,
                const std::vector<std::string>& strs = {});
    std::string serializeToStdString() const;
};



} // namespace tcp_standard_message

typedef QSharedPointer<tcp_standard_message::TCPMessage> TCPMsgStruPtr;

//Q_DECLARE_METATYPE(tcp_standard_message::TCPMessage);
#endif // TCPSTANDARDMESSAGE_H
