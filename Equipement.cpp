/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */
/**
* \file Equipement.cpp
* \brief Abstract Equipement Base Class.
* \author Pierre Weiss
* \date 2009
*/

#include "Equipement.h"
#include "Generator.h"
#include <sstream>

Equipement::Equipement(const size_t &_indice, const std::string &_type)
{
  this->indice = _indice;
  this->nodeName = _type + Generator::toString(_indice);
  this->ip = "0.0.0.0";
  this->mask = "0.0.0.0";
  this->ipInterfaceName = "iface_"+this->nodeName;
  this->x = 0;
  this->y = 0;
  this->nsc = "";
   this->machinesNumber = 1;	
}

Equipement::Equipement(const size_t &_indice, const std::string &_type, const size_t &_machinesNumber)
{
  this->indice = _indice;
  this->nodeName = _type + Generator::toString(_indice);
  this->ip = "0.0.0.0";
  this->mask = "0.0.0.0";
  this->ipInterfaceName = "iface_"+this->nodeName;
  this->x = 0;
  this->y = 0;
  this->nsc = "";	
  this->machinesNumber = _machinesNumber;
}

//no pointer, nothing to destroy
Equipement::~Equipement()
{
}

std::vector<std::string> Equipement::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/helper-module.h\"");

  return headers; 
}

std::vector<std::string> Equipement::GenerateNode()
{
  std::vector<std::string> nodes;
  nodes.push_back("NodeContainer "+this->getNodeName()+";");
  nodes.push_back(this->getNodeName()+".Create("+Generator::toString(this->machinesNumber)+");");

  return nodes; 
}

std::vector<std::string> Equipement::GenerateIpStack()
{
  std::vector<std::string> stack;
  stack.push_back("InternetStackHelper net_"+this->getNodeName()+";");
  if(this->getNsc().compare("") != 0)
  {
    stack.push_back("net_"+this->getNodeName()+".SetNscStack (nscStack);");
  }
  stack.push_back("net_"+this->getNodeName()+".Install ("+this->getNodeName()+");");

  return stack; 
}
  
void Equipement::setNodeName(const std::string &_nodeName)
{
  this->nodeName = _nodeName;
}

void Equipement::setIpv4Address(const std::string &_ip, const std::string &_mask)
{
  this->ip = _ip;
  this->mask = _mask;
}

void Equipement::setIpInterfaceName(const std::string &_ipInterfaceName)
{
  this->ipInterfaceName = _ipInterfaceName;
}

std::string Equipement::getNodeName()
{
  return this->nodeName;
}

std::string Equipement::getNodeName(const size_t &number)
{
  return std::string("NodeContainer("+this->nodeName+".Get("+Generator::toString(number)+"))");
}

std::string Equipement::getIpInterfaceName()
{
  return this->ipInterfaceName;
}
 
void Equipement::setPosition(const size_t &_x, const size_t &_y)
{
  this->x = _x;
  this->y = _y;
}

std::string Equipement::getIp()
{
  return this->ip;
}

std::string Equipement::getMask()
{
  return this->mask;
}

std::string Equipement::getX()
{
  return Generator::toString(this->x);
}

std::string Equipement::getY()
{
  return Generator::toString(this->y);
}

std::string Equipement::getIndice()
{
  return Generator::toString(this->indice);
}

std::string Equipement::getNsc()
{
  return this->nsc;
}
  
void Equipement::setNsc(const std::string &_nsc)
{
  this->nsc = _nsc;
}

size_t Equipement::getMachinesNumber()
{
  return this->machinesNumber;
}





