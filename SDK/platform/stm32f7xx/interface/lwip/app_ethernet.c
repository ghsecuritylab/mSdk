/**
  ******************************************************************************
  * @file    LwIP/LwIP_HTTP_Server_Raw/Src/app_ethernet.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    23-September-2016
  * @brief   Ethernet specefic module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "api/lan_def.h"
#include "interface/LwIp/src/include/lwip/opt.h"
#include "main.h"
//#include "lcd_log.h"
#include "driver/stm32f7xx_hal.h"
#include "interface/LwIp/src/include/lwip/dhcp.h"
#include "app_ethernet.h"
#include "ethernetif.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef USE_DHCP
#define MAX_DHCP_TRIES  4
uint32_t DHCPfineTimer = 0;
volatile uint8_t DHCP_state;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Notify the User about the nework interface config status 
  * @param  netif: the network interface
  * @retval None
  */
void User_notification(struct netif *netif) 
{
  if (netif_is_up(netif))
 {
#ifdef USE_DHCP
    /* Update DHCP state machine */
    DHCP_state = DHCP_START;
#else
#ifdef LWIP_DEBUG_EN
    //uint8_t iptxt[20];
    
    //sprintf((char*)iptxt, "%d.%d.%d.%d", IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    
    uart.printf(DebugCom, "Static IP address: %d.%d.%d.%d\n", IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
 
#else    
    /* Turn On LED 1 to indicate ETH and LwIP init success*/
    //BSP_LED_On(LED1);
#endif /* LWIP_DEBUG_EN */
#endif /* USE_DHCP */
 }
 else
  {  
#ifdef USE_DHCP
    /* Update DHCP state machine */
    DHCP_state = DHCP_LINK_DOWN;
#endif  /* USE_DHCP */
#ifdef LWIP_DEBUG_EN
   uart.puts(DebugCom, "The network cable is not connected \n", -1);
#else    
    /* Turn On LED 2 to indicate ETH and LwIP init error */
    //BSP_LED_On(LED2);
#endif /* LWIP_DEBUG_EN */
  } 
}

/**
  * @brief  This function notify user about link status changement.
  * @param  netif: the network interface
  * @retval None
  */
void ethernetif_notify_conn_changed(struct netif *netif)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

  if(netif_is_link_up(netif))
  {
#ifdef USE_DHCP
#ifdef LWIP_DEBUG_EN
	  uart.puts(DebugCom, "The network cable is now connected \n", -1);
#else
    //BSP_LED_Off(LED2);
    //BSP_LED_On(LED1);
#endif /* LWIP_DEBUG_EN */
    /* Update DHCP state machine */
    DHCP_state = DHCP_START;
#else
    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);    
    DHCP_state = DHCP_ADDRESS_ASSIGNED;
#ifdef LWIP_DEBUG_EN
    //uint8_t iptxt[20];
    
    //sprintf((char*)iptxt, "%d.%d.%d.%d", IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    
    uart.printf(DebugCom, "Static IP address: %d.%d.%d.%d\n", IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
#else
    //BSP_LED_Off(LED2);
    //BSP_LED_On(LED1);
#endif /* LWIP_DEBUG_EN */
#endif /* USE_DHCP */   
    
    netif_set_addr(netif, &ipaddr , &netmask, &gw);
    
    /* When the netif is fully configured this function must be called.*/
    netif_set_up(netif);     
  }
  else
  {
#ifdef USE_DHCP
    /* Update DHCP state machine */
    DHCP_state = DHCP_LINK_DOWN;
#endif /* USE_DHCP */
    
    /*  When the netif link is down this function must be called.*/
    netif_set_down(netif);
    
#ifdef LWIP_DEBUG_EN
    uart.puts(DebugCom, "The network cable is not connected \n", -1);
#else
    //BSP_LED_Off(LED1);
    //BSP_LED_On(LED2);
#endif /* LWIP_DEBUG_EN */
  }
}

#ifdef USE_DHCP
/**
  * @brief  DHCP_Process_Handle
  * @param  None
  * @retval None
  */
void DHCP_Process(struct netif *netif)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;
  uint32_t IPaddress = 0;
  
  switch (DHCP_state)
  {
  case DHCP_START:
    {
      netif->ip_addr.addr = 0;
      netif->netmask.addr = 0;
      netif->gw.addr = 0;
      IPaddress = 0;
      DHCP_state = DHCP_WAIT_ADDRESS;
      dhcp_start(netif);
#ifdef LWIP_DEBUG_EN
      uart.puts(DebugCom, "  State: Looking for DHCP sever ...\n", -1);
#endif
    }
    break;

  case DHCP_WAIT_ADDRESS:
    {
      /* Read the new IP address */
      IPaddress = netif->ip_addr.addr;
      
      if (IPaddress !=0) 
      {
        DHCP_state = DHCP_ADDRESS_ASSIGNED;	
        
        /* Stop DHCP */
        dhcp_stop(netif);

#ifdef LWIP_DEBUG_EN
        uint8_t iptab[4];
        //uint8_t iptxt[20];
  
        iptab[0] = (uint8_t)(IPaddress >> 24);
        iptab[1] = (uint8_t)(IPaddress >> 16);
        iptab[2] = (uint8_t)(IPaddress >> 8);
        iptab[3] = (uint8_t)(IPaddress);

        //sprintf((char*)iptxt, "%d.%d.%d.%d", iptab[3], iptab[2], iptab[1], iptab[0]);

        uart.printf(DebugCom, "IP address assigned by a DHCP server: %d.%d.%d.%d\n", iptab[3], iptab[2], iptab[1], iptab[0]);
#else
     //BSP_LED_On(LED1);
#endif
      }
      else
      {
        /* DHCP timeout */
        if (netif->dhcp->tries > MAX_DHCP_TRIES)
        {
          DHCP_state = DHCP_TIMEOUT;

          /* Stop DHCP */
          dhcp_stop(netif);

          /* Static address used */
          IP4_ADDR(&ipaddr, IP_ADDR0 ,IP_ADDR1 , IP_ADDR2 , IP_ADDR3 );
          IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
          IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
          netif_set_addr(netif, &ipaddr , &netmask, &gw);

#ifdef LWIP_DEBUG_EN
          //uint8_t iptxt[20];
          
          //sprintf((char*)iptxt, "%d.%d.%d.%d", IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
          uart.puts(DebugCom, "DHCP timeout !!\n", -1);
          uart.printf(DebugCom, "Static IP address  : %d.%d.%d.%d\n", IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
#else
     //BSP_LED_On(LED1);
#endif
        }
      }
    }
    break;
  default: break;
  }
}

/**
  * @brief  DHCP periodic check
  * @param  localtime the current LocalTime value
  * @retval None
  */
void DHCP_Periodic_Handle(struct netif *netif)
{  
  /* Fine DHCP periodic process every 500ms */
  if (HAL_GetTick() - DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
  {
    DHCPfineTimer =  HAL_GetTick();
    if ((DHCP_state != DHCP_ADDRESS_ASSIGNED) && 
        (DHCP_state != DHCP_TIMEOUT) &&
          (DHCP_state != DHCP_LINK_DOWN))
    {
      /* process DHCP state machine */
      DHCP_Process(netif);    
    }
  }
}
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
