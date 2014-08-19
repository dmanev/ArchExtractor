#
# emof.py
#
# generated by pyemof v0.11.0 on [Sat Nov  3 21:36:20 2007] 
#
# Copyright (C) 2003-2007, Raphael Marvie 
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.
# http://www.fsf.org/licensing/licenses/gpl.html
#
# Author contact: raphael.marvie@lifl.fr
#

class Enumeration(object):
    def __init__(self, names):
        for number,name in enumerate(names.split()):
            setattr(self, name, number)

class VisibilityKind(Enumeration):
    visibilities = ['unknown', 'private', 'public', 'protected', 'package']    
    def __init__(self):
        super(VisibilityKind, self).__init__(' '.join(VisibilityKind.visibilities))    
    def get_attrName(self, value):
        return VisibilityKind.visibilities[value]

class list_composite(list):

    def __init__(self):
        super(list_composite, self).__init__()

    def append(self, value):
        value.isRoot = False
        super(list_composite, self).append(value)

    def remove(self, value):
        value.isRoot = True
        super(list_composite, self).remove(value)
        

class Element(object):

    _id = 0
    isRoot = True

    def __init__(self, ):
        super(Element, self).__init__()
        Element._id += 1
        self._xmi_id = 'Element:%s' % Element._id

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = True
        del self.visited
        return res    


class Object(Element):

    _id = 0
    isRoot = True

    def __init__(self, ):
        super(Object, self).__init__()
        Object._id += 1
        self._xmi_id = 'Object:%s' % Object._id

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = True
        del self.visited
        return res    

    def getMetaClass(self):
        pass

    def container(self):
        pass

    def equals(self, element):
        pass

    def get(self, property):
        pass

    def set(self, property, element):
        pass

    def isSet(self, property):
        pass

    def unset(self, property):
        pass


class NamedElement(Object):

    _id = 0
    isRoot = True

    def __init__(self, name=None):
        super(NamedElement, self).__init__()
        NamedElement._id += 1
        self._xmi_id = 'NamedElement:%s' % NamedElement._id
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.name == other.name
        del self.visited
        return res    

    def get_name(self):
        return self._name
    def set_name(self, value):
        self._name = value
    name = property(get_name, set_name)

class Tag(Object):

    _id = 0
    isRoot = True

    def __init__(self, name=None, value=None, element=None):
        super(Tag, self).__init__()
        Tag._id += 1
        self._xmi_id = 'Tag:%s' % Tag._id
        self._name = name
        self._value = value
        if not element:
            element = list()
        self._element = element

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.name == other.name and self.value == other.value and self.element == other.element
        del self.visited
        return res    

    def get_name(self):
        return self._name
    def set_name(self, value):
        self._name = value
    name = property(get_name, set_name)

    def get_value(self):
        return self._value
    def set_value(self, value):
        self._value = value
    value = property(get_value, set_value)

    def get_element(self):
        return self._element
    def add_element(self, val):
        self._element.append(val)
    element = property(get_element)

class Component(NamedElement):

    _id = 0
    isRoot = True

    def __init__(self, requiredClass=None, providedClass=None, name=None):
        super(Component, self).__init__()
        Component._id += 1
        self._xmi_id = 'Component:%s' % Component._id
        self._name = name
        if not requiredClass:
            requiredClass = list_composite()        
        self._requiredClass = requiredClass
        if not providedClass:
            providedClass = list_composite()
        self._providedClass = providedClass

    def get_requiredClass(self):
        return self._requiredClass
    def add_requiredClass(self, Value):
        if type(Value) is Class:
            if Value not in self._requiredClass: 
                self._requiredClass.append(Value)
    requiredClass = property(get_requiredClass)

    def get_providedClass(self):
        return self._providedClass
    def add_providedClass(self, Value):
        if type(Value) is Class:
            if Value not in self._providedClass:
                self._providedClass.append(Value)
    providedClass = property(get_providedClass) 

class Package(NamedElement):

    _id = 0
    isRoot = True

    def __init__(self, uri=None, nestedPackage=None, nestingPackage=None, ownedType=None, name=None):
        super(Package, self).__init__()
        Package._id += 1
        self._xmi_id = 'Package:%s' % Package._id
        self._uri = uri
        if not nestedPackage:
            nestedPackage = list_composite()
        self._nestedPackage = nestedPackage
        self._nestingPackage = nestingPackage
        if not ownedType:
            ownedType = list_composite()
        self._ownedType = ownedType
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.uri == other.uri and self.nestedPackage == other.nestedPackage and self.nestingPackage == other.nestingPackage and self.ownedType == other.ownedType and self.name == other.name
        del self.visited
        return res    

    def get_uri(self):
        return self._uri
    def set_uri(self, value):
        self._uri = value
    uri = property(get_uri, set_uri)

    def get_nestedPackage(self):
        return self._nestedPackage
    def add_nestedPackage(self, value, other=True):
        self._nestedPackage.append(value)
        if other:
            value.set_nestingPackage(self, False)
    def del_nestedPackage(self, value, other=True):
        self._nestedPackage.remove(value)
        if other:
            value.del_nestingPackage(self, False)
    nestedPackage = property(get_nestedPackage)

    def get_nestingPackage(self):
        return self._nestingPackage
    def set_nestingPackage(self, value, other=True):
        self._nestingPackage = value
        if other:
            value.add_nestedPackage(self, False)
    def del_nestingPackage(self, other=True):
        if other and self._nestingPackage:
            self._nestingPackage.del_nestedPackage(self, False)
        self._nestingPackage = None
    nestingPackage = property(get_nestingPackage, set_nestingPackage)

    def get_ownedType(self):
        return self._ownedType
    def add_ownedType(self, val):
        self._ownedType.append(val)
    ownedType = property(get_ownedType)


class TypedElement(NamedElement):

    _id = 0
    isRoot = True

    def __init__(self, type=None, name=None, visibility=None):
        super(TypedElement, self).__init__()
        TypedElement._id += 1
        self._xmi_id = 'TypedElement:%s' % TypedElement._id
        self._type = type
        self._name = name
        self._visibility = visibility        

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.type == other.type and self.name == other.name
        del self.visited
        return res    

    def get_type(self):
        return self._type
    def set_type(self, value):
        self._type = value
    type = property(get_type, set_type)
    def get_visibility(self):
        return self._visibility
    def get_visibilityStr(self):
        return VisibilityKind().get_attrName(self.get_visibility())
    visibilityStr = property(get_visibilityStr)    
    def set_visibility(self, visibility):
        self._visibility = visibility
    visibility = property(get_visibility, set_visibility)    

class EnumerationLiteral(NamedElement):

    _id = 0
    isRoot = True

    def __init__(self, enumeration=None, name=None):
        super(EnumerationLiteral, self).__init__()
        EnumerationLiteral._id += 1
        self._xmi_id = 'EnumerationLiteral:%s' % EnumerationLiteral._id
        self._enumeration = enumeration
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.enumeration == other.enumeration and self.name == other.name
        del self.visited
        return res    

    def get_enumeration(self):
        return self._enumeration
    def set_enumeration(self, value, other=True):
        self._enumeration = value
        if other:
            value.add_ownedLiteral(self, False)
    def del_enumeration(self, other=True):
        if other and self._enumeration:
            self._enumeration.del_ownedLiteral(self, False)
        self._enumeration = None
    enumeration = property(get_enumeration, set_enumeration)


class Type(NamedElement):

    _id = 0
    isRoot = True

    def __init__(self, name=None):
        super(Type, self).__init__()
        Type._id += 1
        self._xmi_id = 'Type:%s' % Type._id
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.name == other.name
        del self.visited
        return res    

    def isInstance(self, element):
        pass


class MultiplicityElement(TypedElement):

    _id = 0
    isRoot = True

    def __init__(self, isOrdered=False, isUnique=True, lower=None, upper=None, type=None, name=None):
        super(MultiplicityElement, self).__init__()
        MultiplicityElement._id += 1
        self._xmi_id = 'MultiplicityElement:%s' % MultiplicityElement._id
        self._isOrdered = isOrdered
        self._isUnique = isUnique
        self._lower = lower
        self._upper = upper
        self._type = type
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.isOrdered == other.isOrdered and self.isUnique == other.isUnique and self.lower == other.lower and self.upper == other.upper and self.type == other.type and self.name == other.name
        del self.visited
        return res    

    def get_isOrdered(self):
        return self._isOrdered
    def set_isOrdered(self, value):
        self._isOrdered = value
    isOrdered = property(get_isOrdered, set_isOrdered)

    def get_isUnique(self):
        return self._isUnique
    def set_isUnique(self, value):
        self._isUnique = value
    isUnique = property(get_isUnique, set_isUnique)

    def get_lower(self):
        return self._lower
    def set_lower(self, value):
        self._lower = value
    lower = property(get_lower, set_lower)

    def get_upper(self):
        return self._upper
    def set_upper(self, value):
        self._upper = value
    upper = property(get_upper, set_upper)


class DataType(Type):

    _id = 0
    isRoot = True

    def __init__(self, serializable=None, defaultValue=None, allowNull=None, name=None):
        super(DataType, self).__init__()
        DataType._id += 1
        self._xmi_id = 'DataType:%s' % DataType._id
        self._serializable = serializable
        self._defaultValue = defaultValue
        self._allowNull = allowNull
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.serializable == other.serializable and self.defaultValue == other.defaultValue and self.allowNull == other.allowNull and self.name == other.name
        del self.visited
        return res    

    def get_serializable(self):
        return self._serializable
    def set_serializable(self, value):
        self._serializable = value
    serializable = property(get_serializable, set_serializable)

    def get_defaultValue(self):
        return self._defaultValue
    def set_defaultValue(self, value):
        self._defaultValue = value
    defaultValue = property(get_defaultValue, set_defaultValue)

    def get_allowNull(self):
        return self._allowNull
    def set_allowNull(self, value):
        self._allowNull = value
    allowNull = property(get_allowNull, set_allowNull)


class Class(Type):

    _id = 0
    isRoot = True

    def __init__(self, isAbstract=False, ownedAttribute=None, ownedOperation=None, superClass=None, name=None):
        super(Class, self).__init__()
        Class._id += 1
        self._xmi_id = 'Class:%s' % Class._id
        self._isAbstract = isAbstract
        if not ownedAttribute:
            ownedAttribute = list_composite()
        self._ownedAttribute = ownedAttribute
        if not ownedOperation:
            ownedOperation = list_composite()
        self._ownedOperation = ownedOperation
        if not superClass:
            superClass = list()
        self._superClass = superClass
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.isAbstract == other.isAbstract and self.ownedAttribute == other.ownedAttribute and self.ownedOperation == other.ownedOperation and self.superClass == other.superClass and self.name == other.name
        del self.visited
        return res    

    def get_isAbstract(self):
        return self._isAbstract
    def set_isAbstract(self, value):
        self._isAbstract = value
    isAbstract = property(get_isAbstract, set_isAbstract)

    def get_ownedAttribute(self):
        return self._ownedAttribute
    def add_ownedAttribute(self, value, other=True):
        self._ownedAttribute.append(value)
        if other:
            value.set_class_(self, False)
    def del_ownedAttribute(self, value, other=True):
        self._ownedAttribute.remove(value)
        if other:
            value.del_class_(self, False)
    ownedAttribute = property(get_ownedAttribute)

    def get_ownedOperation(self):
        return self._ownedOperation
    def add_ownedOperation(self, value, other=True):
        self._ownedOperation.append(value)
        if other:
            value.set_class_(self, False)
    def del_ownedOperation(self, value, other=True):
        self._ownedOperation.remove(value)
        if other:
            value.del_class_(self, False)
    ownedOperation = property(get_ownedOperation)

    def get_superClass(self):
        return self._superClass
    def add_superClass(self, val):
        self._superClass.append(val)
    superClass = property(get_superClass)


class Operation(MultiplicityElement):

    _id = 0
    isRoot = True

    def __init__(self, raisedException=None, ownedParameter=None, class_=None, isOrdered=False, isUnique=True, lower=None, upper=None, type=None, name=None):
        super(Operation, self).__init__()
        Operation._id += 1
        self._xmi_id = 'Operation:%s' % Operation._id
        if not raisedException:
            raisedException = list()
        self._raisedException = raisedException
        if not ownedParameter:
            ownedParameter = list_composite()
        self._ownedParameter = ownedParameter
        self._class_ = class_
        self._isOrdered = isOrdered
        self._isUnique = isUnique
        self._lower = lower
        self._upper = upper
        self._type = type
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.raisedException == other.raisedException and self.ownedParameter == other.ownedParameter and self.class_ == other.class_ and self.isOrdered == other.isOrdered and self.isUnique == other.isUnique and self.lower == other.lower and self.upper == other.upper and self.type == other.type and self.name == other.name
        del self.visited
        return res    

    def get_raisedException(self):
        return self._raisedException
    def add_raisedException(self, val):
        self._raisedException.append(val)
    raisedException = property(get_raisedException)

    def get_ownedParameter(self):
        return self._ownedParameter
    def add_ownedParameter(self, value, other=True):
        self._ownedParameter.append(value)
        if other:
            value.add_operation(self, False)
    def del_ownedParameter(self, value, other=True):
        self._ownedParameter.remove(value)
        if other:
            value.del_operation(self, False)
    ownedParameter = property(get_ownedParameter)

    def get_class_(self):
        return self._class_
    def set_class_(self, value, other=True):
        self._class_ = value
        if other:
            value.add_ownedOperation(self, False)
    def del_class_(self, other=True):
        if other and self._class_:
            self._class_.del_ownedOperation(self, False)
        self._class_ = None
    class_ = property(get_class_, set_class_)


class Parameter(MultiplicityElement):

    _id = 0
    isRoot = True

    def __init__(self, operation=None, isOrdered=False, isUnique=True, lower=None, upper=None, type=None, name=None):
        super(Parameter, self).__init__()
        Parameter._id += 1
        self._xmi_id = 'Parameter:%s' % Parameter._id
        if not operation:
            operation = list()
        self._operation = operation
        self._isOrdered = isOrdered
        self._isUnique = isUnique
        self._lower = lower
        self._upper = upper
        self._type = type
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.operation == other.operation and self.isOrdered == other.isOrdered and self.isUnique == other.isUnique and self.lower == other.lower and self.upper == other.upper and self.type == other.type and self.name == other.name
        del self.visited
        return res    

    def get_operation(self):
        return self._operation
    def add_operation(self, value, other=True):
        self._operation.append(value)
        if other:
            value.add_ownedParameter(self, False)
    def del_operation(self, value, other=True):
        self._operation.remove(value)
        if other:
            value.del_ownedParameter(self, False)
    operation = property(get_operation)


class Property(MultiplicityElement):

    _id = 0
    isRoot = True

    def __init__(self, isReadOnly=False, default=None, isComposite=False, isDerived=False, isId=None, opposite=None, class_=None, isOrdered=False, isUnique=True, lower=None, upper=None, type=None, name=None):
        super(Property, self).__init__()
        Property._id += 1
        self._xmi_id = 'Property:%s' % Property._id
        self._isReadOnly = isReadOnly
        self._default = default
        self._isComposite = isComposite
        self._isDerived = isDerived
        self._isId = isId
        self._opposite = opposite
        self._class_ = class_
        self._isOrdered = isOrdered
        self._isUnique = isUnique
        self._lower = lower
        self._upper = upper
        self._type = type
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.isReadOnly == other.isReadOnly and self.default == other.default and self.isComposite == other.isComposite and self.isDerived == other.isDerived and self.isId == other.isId and self.opposite == other.opposite and self.class_ == other.class_ and self.isOrdered == other.isOrdered and self.isUnique == other.isUnique and self.lower == other.lower and self.upper == other.upper and self.type == other.type and self.name == other.name
        del self.visited
        return res    

    def get_isReadOnly(self):
        return self._isReadOnly
    def set_isReadOnly(self, value):
        self._isReadOnly = value
    isReadOnly = property(get_isReadOnly, set_isReadOnly)

    def get_default(self):
        return self._default
    def set_default(self, value):
        self._default = value
    default = property(get_default, set_default)

    def get_isComposite(self):
        return self._isComposite
    def set_isComposite(self, value):
        self._isComposite = value
    isComposite = property(get_isComposite, set_isComposite)

    def get_isDerived(self):
        return self._isDerived
    def set_isDerived(self, value):
        self._isDerived = value
    isDerived = property(get_isDerived, set_isDerived)

    def get_isId(self):
        return self._isId
    def set_isId(self, value):
        self._isId = value
    isId = property(get_isId, set_isId)

    def get_opposite(self):
        return self._opposite
    def set_opposite(self, value):
        self._opposite = value
    opposite = property(get_opposite, set_opposite)

    def get_class_(self):
        return self._class_
    def set_class_(self, value, other=True):
        self._class_ = value
        if other:
            value.add_ownedAttribute(self, False)
    def del_class_(self, other=True):
        if other and self._class_:
            self._class_.del_ownedAttribute(self, False)
        self._class_ = None
    class_ = property(get_class_, set_class_)


class Enumeration(DataType):

    _id = 0
    isRoot = True

    def __init__(self, ownedLiteral=None, serializable=None, defaultValue=None, allowNull=None, name=None):
        super(Enumeration, self).__init__()
        Enumeration._id += 1
        self._xmi_id = 'Enumeration:%s' % Enumeration._id
        if not ownedLiteral:
            ownedLiteral = list_composite()
        self._ownedLiteral = ownedLiteral
        self._serializable = serializable
        self._defaultValue = defaultValue
        self._allowNull = allowNull
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.ownedLiteral == other.ownedLiteral and self.serializable == other.serializable and self.defaultValue == other.defaultValue and self.allowNull == other.allowNull and self.name == other.name
        del self.visited
        return res    

    def get_ownedLiteral(self):
        return self._ownedLiteral
    def add_ownedLiteral(self, value, other=True):
        self._ownedLiteral.append(value)
        if other:
            value.set_enumeration(self, False)
    def del_ownedLiteral(self, value, other=True):
        self._ownedLiteral.remove(value)
        if other:
            value.del_enumeration(self, False)
    ownedLiteral = property(get_ownedLiteral)


class PrimitiveType(DataType):

    _id = 0
    isRoot = True

    def __init__(self, serializable=None, defaultValue=None, allowNull=None, name=None):
        super(PrimitiveType, self).__init__()
        PrimitiveType._id += 1
        self._xmi_id = 'PrimitiveType:%s' % PrimitiveType._id
        self._serializable = serializable
        self._defaultValue = defaultValue
        self._allowNull = allowNull
        self._name = name

    def __eq__(self, other):
        if hasattr(self, 'visited'):
            return True
        if type(self) != type(other):
            return False
        self.visited = None
        res = self.serializable == other.serializable and self.defaultValue == other.defaultValue and self.allowNull == other.allowNull and self.name == other.name
        del self.visited
        return res    


class Integer(PrimitiveType):

    _id = 0
    isRoot = True

    def __init__(self, ):
        super(Integer, self).__init__()
        Integer._id += 1
        self._xmi_id = 'Integer:%s' % Integer._id


class Boolean(PrimitiveType):

    _id = 0
    isRoot = True

    def __init__(self, ):
        super(Boolean, self).__init__()
        Boolean._id += 1
        self._xmi_id = 'Boolean:%s' % Boolean._id


class String(PrimitiveType):

    _id = 0
    isRoot = True

    def __init__(self, ):
        super(String, self).__init__()
        String._id += 1
        self._xmi_id = 'String:%s' % String._id


class Repository(object):

    def __init__(self):
        super(Repository, self).__init__()
        self._Object = list()
        self._Tag = list()
        self._Component = list()
        self._Package = list()
        self._EnumerationLiteral = list()
        self._Class = list()
        self._Operation = list()
        self._Parameter = list()
        self._Property = list()
        self._Enumeration = list()
        self._PrimitiveType = list()
        self._DataType = list()

    def get_Object(self):
        return self._Object
    def add_Object(self, val):
        self._Object.append(val)
    Object = property(get_Object)

    def get_Tag(self):
        return self._Tag
    def add_Tag(self, val):
        self._Tag.append(val)
    Tag = property(get_Tag)

    def get_Component(self):
        return self._Component
    def add_Component(self, val):
        self._Component.append(val)
    Component = property(get_Component)
    def get_Package(self):
        return self._Package
    def add_Package(self, val):
        self._Package.append(val)
    Package = property(get_Package)

    def get_EnumerationLiteral(self):
        return self._EnumerationLiteral
    def add_EnumerationLiteral(self, val):
        self._EnumerationLiteral.append(val)
    EnumerationLiteral = property(get_EnumerationLiteral)

    def get_Class(self):
        return self._Class
    def add_Class(self, val):
        self._Class.append(val)
    Class = property(get_Class)

    def get_Operation(self):
        return self._Operation
    def add_Operation(self, val):
        self._Operation.append(val)
    Operation = property(get_Operation)

    def get_Parameter(self):
        return self._Parameter
    def add_Parameter(self, val):
        self._Parameter.append(val)
    Parameter = property(get_Parameter)

    def get_Property(self):
        return self._Property
    def add_Property(self, val):
        self._Property.append(val)
    Property = property(get_Property)

    def get_Enumeration(self):
        return self._Enumeration
    def add_Enumeration(self, val):
        self._Enumeration.append(val)
    Enumeration = property(get_Enumeration)

    def get_PrimitiveType(self):
        return self._PrimitiveType
    def add_PrimitiveType(self, val):
        self._PrimitiveType.append(val)
    PrimitiveType = property(get_PrimitiveType)
    
    def get_DataType(self):
        return self._DataType
    def add_DataType(self, val):
        self._DataType.append(val)
    DataType = property(get_DataType)


class Factory(object):

    def __init__(self, repository):
        super(Factory, self).__init__()
        self._repository = repository

    def create_Object(self):
        o = Object()
        self._repository.Object.append(o)
        return o

    def create_Tag(self):
        o = Tag()
        self._repository.Tag.append(o)
        return o
    
    def create_Component(self):
        o = Component()
        self._repository.Component.append(o)
        return o

    def create_Package(self):
        o = Package()
        self._repository.Package.append(o)
        return o

    def create_EnumerationLiteral(self):
        o = EnumerationLiteral()
        self._repository.EnumerationLiteral.append(o)
        return o

    def create_Class(self):
        o = Class()
        self._repository.Class.append(o)
        return o

    def create_Operation(self):
        o = Operation()
        self._repository.Operation.append(o)
        return o

    def create_Parameter(self):
        o = Parameter()
        self._repository.Parameter.append(o)
        return o

    def create_Property(self):
        o = Property()
        self._repository.Property.append(o)
        return o

    def create_Enumeration(self):
        o = Enumeration()
        self._repository.Enumeration.append(o)
        return o

    def create_PrimitiveType(self):
        o = PrimitiveType()
        self._repository.PrimitiveType.append(o)
        return o

    def create_DataType(self):
        o = DataType()
        self._repository.DataType.append(o)
        return o
# eof
