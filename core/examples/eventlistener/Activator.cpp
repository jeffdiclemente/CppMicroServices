/*=============================================================================

  Library: CppMicroServices

  Copyright (c) The CppMicroServices developers. See the COPYRIGHT
  file at the top-level directory of this distribution and at
  https://github.com/saschazelzer/CppMicroServices/COPYRIGHT .

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

//! [Activator]
#include <usBundleActivator.h>
#include <usBundleContext.h>

US_USE_NAMESPACE

namespace {

/**
 * This class implements a simple bundle that utilizes the CppMicroServices's
 * event mechanism to listen for service events. Upon receiving a service event,
 * it prints out the event's details.
 */
class Activator : public BundleActivator
{

private:

  /**
   * Implements BundleActivator::Start(). Prints a message and adds a member
   * function to the bundle context as a service listener.
   *
   * @param context the framework context for the bundle.
   */
  void Start(BundleContext* context)
  {
    std::cout << "Starting to listen for service events." << std::endl;
    context->AddServiceListener(this, &Activator::ServiceChanged);
  }

  /**
   * Implements BundleActivator::Stop(). Prints a message and removes the
   * member function from the bundle context as a service listener.
   *
   * @param context the framework context for the bundle.
   */
  void Stop(BundleContext* context)
  {
    context->RemoveServiceListener(this, &Activator::ServiceChanged);
    std::cout << "Stopped listening for service events." << std::endl;

    // Note: It is not required that we remove the listener here,
    // since the framework will do it automatically anyway.
  }

  /**
   * Prints the details of any service event from the framework.
   *
   * @param event the fired service event.
   */
  void ServiceChanged(const ServiceEvent event)
  {
    std::string objectClass = ref_any_cast<std::vector<std::string> >(event.GetServiceReference().GetProperty(ServiceConstants::OBJECTCLASS())).front();

    if (event.GetType() == ServiceEvent::REGISTERED)
    {
      std::cout << "Ex1: Service of type " << objectClass << " registered." << std::endl;
    }
    else if (event.GetType() == ServiceEvent::UNREGISTERING)
    {
      std::cout << "Ex1: Service of type " << objectClass << " unregistered." << std::endl;
    }
    else if (event.GetType() == ServiceEvent::MODIFIED)
    {
      std::cout << "Ex1: Service of type " << objectClass << " modified." << std::endl;
    }
  }
};

}

US_EXPORT_BUNDLE_ACTIVATOR(Activator)
//! [Activator]
