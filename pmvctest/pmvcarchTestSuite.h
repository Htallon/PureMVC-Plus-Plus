/* 
 * File:   pmvcarchTestSuite.h
 * Author: schell = Schell Scivally
 *
 * Created on November 18, 2009, 10:01 PM
 */

#ifndef _PMVCARCHTESTSUITE_H
#define	_PMVCARCHTESTSUITE_H

#include <iostream>

// cxxtest
#include <cxxtest/TestSuite.h>
// our basic fpatterns
#include <../pmvcpparch/patterns.h>
// Base classes of pmvcpp
#include <../pmvcpparch/pmvcppbase.h>
// Main classes of pmvcpp
#include <../pmvcpparch/pmvcpparch.h>
// Exception classes of pmvcpp
#include <../pmvcpparch/pmvcppexp.h>

//--------------------------------------
//  ALL
//--------------------------------------
class NotesTestSuite : public CxxTest::TestSuite
{
public:
    void testToDoList()
    {
        TS_WARN("Facade is not fully implemented.");
        TS_WARN("Notifier is not fully implemented.");
        TS_WARN("SimpleCommand is not fully implemented.");
        TS_WARN("Model is not fully implemented.");
    }
};
//--------------------------------------
//  Patterns
//--------------------------------------
class MultitonTestSuite : public CxxTest::TestSuite
{
public:
    void testCreateInstances()
    {
        Object* single_1 = Multiton<Object>::instance();
        Object* single_2 = Multiton<Object>::instance();
        Object* single_3 = Multiton<Object>::instance("instance3");
//        TS_TRACE("Address of multiton 1:");
//        TS_TRACE(&*single_1);
//        TS_TRACE("Address of multiton 2:");
//        TS_TRACE(&*single_2);
//        TS_TRACE("Address of multiton 3 (should differ):");
//        TS_TRACE(&*single_3);
        TS_ASSERT_EQUALS(&*single_1, &*single_2);
        TS_ASSERT_DIFFERS(&*single_1, &*single_3);
    }
    void testNumberInstances()
    {
        Multiton<Object>::clear();
        TS_ASSERT_EQUALS(Multiton<Object>::size(), (size_t) 0);
        Multiton<Object>::instance();
        TS_ASSERT_EQUALS(Multiton<Object>::size(), (size_t) 1);
        Multiton<Object>::instance();
        TS_ASSERT_EQUALS(Multiton<Object>::size(), (size_t) 1);
        Multiton<Object>::instance("new instance");
        TS_ASSERT_EQUALS(Multiton<Object>::size(), (size_t) 2);
    }
};
//--------------------------------------
//  IBody
//--------------------------------------
class IBodyTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->type = "thebodytype";
        this->body = new IBody();
    }
    void testCanSetGet_type()
    {
        this->body->setType(type);
        TS_ASSERT_EQUALS(this->body->getType(), type);
    }
    void testConstructor_Sets_type()
    {
        this->body = new IBody(this->type);
        TS_ASSERT_EQUALS(this->body->getType(), this->type);
    }

    IBody* body;
    std::string type;
};
//--------------------------------------
//  Facade
//--------------------------------------
/**
 *  An application facade.
 *  Application facade used for testing the facade.
 */
class ApplicationFacade : public Facade
{
public:
    static ApplicationFacade* instance(std::string key)
    {
        ApplicationFacade* inst = Multiton<ApplicationFacade>::instance(key);
        inst->setMultitonKey(key);
        return inst;
    }
    IController* getController()
    {
        return this->controller;
    }
protected:
    void initializeController()
    {
        // call super
        Facade::initializeController();
    }
};
class FacadeTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->appKey = "testAppFacadeKey";
        this->appFacade = ApplicationFacade::instance(this->appKey);
        this->appFacade->setMultitonKey(this->appKey);
    }
    void tearDown()
    {
        Multiton<ApplicationFacade>::clear();
    }
    void testMultitonKeySet()
    {
        TS_ASSERT_EQUALS(this->appFacade->getMultitonKey(), this->appKey);
    }
    void testControllerInitialized()
    {
        // compare to null ptr
        TS_TRACE("appFacade controller mem address:");
        TS_TRACE(&*this->appFacade->getController());
        TS_TRACE("null IController* mem address:");
        TS_TRACE( &*((IController*) 0) );
        TS_ASSERT_DIFFERS(this->appFacade->getController(), (IController*) 0);
    }
    std::string appKey;
    ApplicationFacade* appFacade;
};
//--------------------------------------
//  Notifier
//--------------------------------------
class NotifierTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->notifier = new Notifier();
        this->key = "testNotifierMultitonKey";
    }

    void testCanInitialize()
    {
        this->notifier->initializeNotifier(this->key);
        TS_ASSERT_EQUALS(this->notifier->getMultitonKey(), this->key);
    }

    Notifier* notifier;
    std::string key;
};
//--------------------------------------
//  Model
//--------------------------------------
class testModel : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->key = "testModelMultitonKey";
        this->model = new Model(this->key);
    }
    void testConstructor_Sets_multitonKey()
    {
        this->model = new Model(this->key);
        TS_ASSERT_EQUALS(this->model->getMultitonKey(), this->key);
    }

    Model* model;
    std::string key;
};
#endif	/* _PMVCARCHTESTSUITE_H */