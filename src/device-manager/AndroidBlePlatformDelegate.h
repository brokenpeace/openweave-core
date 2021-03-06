/*
 *
 *    Copyright (c) 2014-2017 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#ifndef ANDROID_BLEPLATFORMDELEGATE_H_
#define ANDROID_BLEPLATFORMDELEGATE_H_

#include <BleLayer/BleLayer.h>
#include <BleLayer/BlePlatformDelegate.h>
#include "WeaveDeviceManager.h"

using namespace nl::Ble;
using namespace nl::Weave::DeviceManager;

typedef bool (*SendWriteRequestCallback)(BLE_CONNECTION_OBJECT connObj, const uint8_t *svcId, const uint8_t *charId, const uint8_t *data, uint32_t dataLen);
typedef bool (*SubscribeCharacteristicCallback)(BLE_CONNECTION_OBJECT connObj, const uint8_t *svcId, const uint8_t *charId);
typedef bool (*UnsubscribeCharacteristicCallback)(BLE_CONNECTION_OBJECT connObj, const uint8_t *svcId, const uint8_t *charId);
typedef bool (*CloseConnectionCallback)(BLE_CONNECTION_OBJECT connObj);
typedef uint16_t (*GetMTUCallback)(BLE_CONNECTION_OBJECT connObj);

class AndroidBlePlatformDelegate :
    public nl::Ble::BlePlatformDelegate
{
public:
    BleLayer *Ble;
    SendWriteRequestCallback SendWriteRequestCb;
    SubscribeCharacteristicCallback SubscribeCharacteristicCb;
    UnsubscribeCharacteristicCallback UnsubscribeCharacteristicCb;
    CloseConnectionCallback CloseConnectionCb;
    GetMTUCallback GetMTUCb;

    // ctor
    AndroidBlePlatformDelegate(BleLayer *ble);

    // Virtuals from BlePlatformDelegate:
    bool SubscribeCharacteristic(BLE_CONNECTION_OBJECT connObj, const nl::Ble::WeaveBleUUID *svcId, const nl::Ble::WeaveBleUUID *charId);
    bool UnsubscribeCharacteristic(BLE_CONNECTION_OBJECT connObj, const nl::Ble::WeaveBleUUID *svcId, const nl::Ble::WeaveBleUUID *charId);
    uint16_t GetMTU(BLE_CONNECTION_OBJECT connObj) const;
    bool CloseConnection(BLE_CONNECTION_OBJECT connObj);
    bool SendIndication(BLE_CONNECTION_OBJECT connObj, const nl::Ble::WeaveBleUUID *svcId, const nl::Ble::WeaveBleUUID *charId, PacketBuffer *pBuf);
    bool SendWriteRequest(BLE_CONNECTION_OBJECT connObj, const nl::Ble::WeaveBleUUID *svcId, const nl::Ble::WeaveBleUUID *charId, PacketBuffer *pBuf);
    bool SendReadRequest(BLE_CONNECTION_OBJECT connObj, const nl::Ble::WeaveBleUUID *svcId, const nl::Ble::WeaveBleUUID *charId, PacketBuffer *pBuf);
    bool SendReadResponse(BLE_CONNECTION_OBJECT connObj, BLE_READ_REQUEST_CONTEXT requestContext, const nl::Ble::WeaveBleUUID *svcId, const nl::Ble::WeaveBleUUID *charId);

    void SetSendWriteRequestCallback(SendWriteRequestCallback cb);
    void SetSubscribeCharacteristicCallback(SubscribeCharacteristicCallback cb);
    void SetUnsubscribeCharacteristicCallback(UnsubscribeCharacteristicCallback cb);
    void SetCloseConnectionCallback(CloseConnectionCallback cb);
    void SetGetMTUCallback(GetMTUCallback cb);
};

#endif /* ANDROID_BLEPLATFORMDELEGATE_H_ */
