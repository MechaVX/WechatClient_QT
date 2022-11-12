#include "listmessageitem.h"
#include "friendbriefinfo.h"
#include "friendmessagebriefwidget.h"
#include "globaldefine.h"
#include <QWidget>
#include <QDebug>



ListMessageItem::ListMessageItem(): frnd_info(nullptr)
{

}

void ListMessageItem::init(QListWidget *list_wid, FriendBriefInfo *frnd_info)
{
    this->list_wid = list_wid;
    this->frnd_info = new FriendBriefInfo;
    this->frnd_info->operator=(*frnd_info);
    frnd_wnd = new FriendMessageBriefWidget;
    frnd_wnd->init(*frnd_info);
    this->setSizeHint(QSize(0, frnd_wnd->height()));
    //防止在msgs_list为空时执行排序，先插入一个空白的信息
    msgs_list.push_back({QTime::currentTime()});

    list_wid->addItem(this);
    //list_wid->insertItem(0, this);
    list_wid->setItemWidget(this, frnd_wnd);
}

ListMessageItem::~ListMessageItem()
{
    if (frnd_info != nullptr)
        delete frnd_info;
}


bool ListMessageItem::operator<(const QListWidgetItem &item) const
{
    //三种重载方式都可
    if (typeid (*this) == typeid (item))
    {
        const ListMessageItem& other_item = dynamic_cast<const ListMessageItem&>(item);
        return this->msgs_list.back().time < other_item.msgs_list.back().time;
    }
    //如果QListWidgetItem不能转为ListMessageItem，则按照基类的排列方式
    return this->QListWidgetItem::operator<(item);
    /*
    try {
        const ListMessageItem& other_item = dynamic_cast<const ListMessageItem&>(item);
        return this->msgs_list.back().time < other_item.msgs_list.back().time;
    } catch (std::bad_cast) {
        //需要#include <typeinfo>才能用该异常
    }
    return this->QListWidgetItem::operator<(item);
    */

    /*
    const ListMessageItem *ptr_item = dynamic_cast<const ListMessageItem*>(&item);
    if (ptr_item == nullptr)
    {

        qDebug() << "ListMessageItem::operator< : ptr_item == nullptr";
        return this->QListWidgetItem::operator<(item);
    }
    return this->msgs_list.back().time < ptr_item->msgs_list.back().time;
    */
}

void ListMessageItem::receiveNewMessage(const communication_message::Message& msg_stru)
{
    //如果一直调用FriendDetailWidget::executeOperationToUser并且str == "发送消息"，将会有大量占位的msg_stru储存在msgs_list中
    msgs_list.push_back(msg_stru);
    frnd_wnd->flushMessageDisplay(msg_stru);
    list_wid->sortItems(Qt::DescendingOrder);
}
