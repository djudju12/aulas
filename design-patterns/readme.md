# Design Patterns 

### [Book]
___

<br>

### What is a Design Pattern?
___
 
1. Pattern **name**
2. **Problem** describes when to apply the pattern
3. **Solution** elements that make up the pattern
4. **Consequences** of the implementation

<br>

### The Catalog of Design Patterns 
___

[Abstract Factory](#abstract-factory) provide an interface for ccreating families of related or dependent objects without specifying their concrete classes 

[Adapter](#adapter) convert the interface of a class into another interface fclients expect. Adapter lets classes work together that couldnt otherwise because of incompatible interfaces 

[Bridge](#bridge) decouple and abstraction from its implementation so that the two can vary independently

[Builder](#builder) separete the construtction of a complex object from its representation so that the same construction process can create different representations

[Chain of Responsibility](#Chain_of_Responsibility) avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the cain until an object handles it 

[Command](#Command) encapsulate a request as and object, thereby letting you parameterize clients with different requests, queue or log requests, and support unbdoable operations

[Composite](#Composite) com,pose objects into tree structures to represet part-whole hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly

[Decorator](#decorator) attach additional responsibilities to and object dynamically. Decorators provide a flexible alternative to subclassing for exting functionality 

[Facade](#Facade) provide a unified interface to a set of interfaces in a subsystem. Facade defines a higher-level interface that makes the subsystem easier to use

[Factory Method](#Factory_Method) define an interface for creating an object, but let subclasses decide which class to instantiate. Factory method lets a class defer instantiation to subclasses

[Flyweight](#Flyweight) use sharing to support large numbers of fine-grained objects efficiently

[Interpreter](#Interpreter) given a language, define a represention for its grammar along weith an interpreter that uses the represenbtation to interpret sentences in the language *

[Mediator](#Mediator) define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently 

[Memento](#Memento) without violating encapsulation, capture and externalize and objects internal state so that the object can be restored to this state later

[Observer](#Observer) define a one-to-many dependency between objects so that when one objects change state, all its dependents are notified and updated automatically

[Prototype](#Prototype) specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype

[Proxy](#Proxy) provide a surrogate (substitute) or placeholder for another objecto to control access to it

[Singleton](#Singleton) ensure a class only has one instance and provide a global point of access to it

[State](#State) allow an object to alter its behavior when its internal state changes. The object will appear to change its class.

[Strategy](#Strategy) define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

[Template Method](#Template_Method) define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Template method lets subclasses redefine certain steps of an algorithm without changing the algorithm structure

[Visitor](#Visitor) represent an operation to be perfomed on the elements of an object structure. Visitor lets you define a new operation without changing the classes of the elements on which its operates.

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-nto1{background-color:#000000;border-color:inherit;text-align:left;vertical-align:top}
.tg .tg-c3ow{border-color:inherit;text-align:center;vertical-align:top}
.tg .tg-0lax{text-align:left;vertical-align:top}
.tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-nto1" colspan="2" rowspan="2"></th>
    <th class="tg-c3ow" colspan="3">Pupose</th>
  </tr>
  <tr>
    <th class="tg-0lax">Creational</th>
    <th class="tg-0lax">Structural</th>
    <th class="tg-0lax">Behavioral</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-0pky" rowspan="5">Scope</td>
    <td class="tg-0pky">Class</td>
    <td class="tg-0pky">Factory Method</td>
    <td class="tg-0lax">Adapter</td>
    <td class="tg-0pky">Interpreter<br><br>Template Method</td>
  </tr>
  <tr>
    <td class="tg-0pky" rowspan="4">Object</td>
    <td class="tg-0pky" rowspan="4">Abstract Factory<br>Builder<br>Prototype<br>Singleton</td>
    <td class="tg-0lax" rowspan="4">Adapter<br>Bridge<br>Composite<br>Decorator<br>Facade<br>Flyweight<br>Proxy</td>
    <td class="tg-0pky" rowspan="4">Chain oif Responsibility<br>Command<br>Iterator<br>Mediator<br>Memento<br>Observer<br>State<br>Strategy<br>Visitor</td>
  </tr>
  <tr>
  </tr>
  <tr>
  </tr>
  <tr>
  </tr>
</tbody>
</table>