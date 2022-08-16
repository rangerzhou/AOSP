/*
 * This file is auto-generated.  DO NOT MODIFY.
 */
package android.os;
/**
 * Basic interface for finding and publishing system services.
 * 
 * You likely want to use android.os.ServiceManager in Java or
 * android::IServiceManager in C++ in order to use this interface.
 * 
 * @hide
 */
public interface IServiceManager extends android.os.IInterface
{
  /** Default implementation for IServiceManager. */
  public static class Default implements android.os.IServiceManager
  {
    /**
     * Retrieve an existing service called @a name from the
     * service manager.
     * 
     * This is the same as checkService (returns immediately) but
     * exists for legacy purposes.
     * 
     * Returns null if the service does not exist.
     */
    @Override public android.os.IBinder getService(java.lang.String name) throws android.os.RemoteException
    {
      return null;
    }
    /**
     * Retrieve an existing service called @a name from the service
     * manager. Non-blocking. Returns null if the service does not
     * exist.
     */
    @Override public android.os.IBinder checkService(java.lang.String name) throws android.os.RemoteException
    {
      return null;
    }
    /**
     * Place a new @a service called @a name into the service
     * manager.
     */
    @Override public void addService(java.lang.String name, android.os.IBinder service, boolean allowIsolated, int dumpPriority) throws android.os.RemoteException
    {
    }
    /** Return a list of all currently running services. */
    @Override public java.lang.String[] listServices(int dumpPriority) throws android.os.RemoteException
    {
      return null;
    }
    /** Request a callback when a service is registered. */
    @Override public void registerForNotifications(java.lang.String name, android.os.IServiceCallback callback) throws android.os.RemoteException
    {
    }
    /** Unregisters all requests for notifications for a specific callback. */
    @Override public void unregisterForNotifications(java.lang.String name, android.os.IServiceCallback callback) throws android.os.RemoteException
    {
    }
    /**
     * Returns whether a given interface is declared on the device, even if it
     * is not started yet. For instance, this could be a service declared in the VINTF
     * manifest.
     */
    @Override public boolean isDeclared(java.lang.String name) throws android.os.RemoteException
    {
      return false;
    }
    /**
     * Returns all declared instances for a particular interface.
     * 
     * For instance, if 'android.foo.IFoo/foo' is declared, and 'android.foo.IFoo' is
     * passed here, then ["foo"] would be returned.
     */
    @Override public java.lang.String[] getDeclaredInstances(java.lang.String iface) throws android.os.RemoteException
    {
      return null;
    }
    /** If updatable-via-apex, returns the APEX via which this is updated. */
    @Override public java.lang.String updatableViaApex(java.lang.String name) throws android.os.RemoteException
    {
      return null;
    }
    /** If connection info is available for the given instance, returns the ConnectionInfo */
    @Override public android.os.ConnectionInfo getConnectionInfo(java.lang.String name) throws android.os.RemoteException
    {
      return null;
    }
    /**
     * Request a callback when the number of clients of the service changes.
     * Used by LazyServiceRegistrar to dynamically stop services that have no clients.
     */
    @Override public void registerClientCallback(java.lang.String name, android.os.IBinder service, android.os.IClientCallback callback) throws android.os.RemoteException
    {
    }
    /** Attempt to unregister and remove a service. Will fail if the service is still in use. */
    @Override public void tryUnregisterService(java.lang.String name, android.os.IBinder service) throws android.os.RemoteException
    {
    }
    /** Get debug information for all currently registered services. */
    @Override public android.os.ServiceDebugInfo[] getServiceDebugInfo() throws android.os.RemoteException
    {
      return null;
    }
    @Override
    public android.os.IBinder asBinder() {
      return null;
    }
  }
  /** Local-side IPC implementation stub class. */
  public static abstract class Stub extends android.os.Binder implements android.os.IServiceManager
  {
    /** Construct the stub at attach it to the interface. */
    public Stub()
    {
      this.attachInterface(this, DESCRIPTOR);
    }
    /**
     * Cast an IBinder object into an android.os.IServiceManager interface,
     * generating a proxy if needed.
     */
    public static android.os.IServiceManager asInterface(android.os.IBinder obj)
    {
      if ((obj==null)) {
        return null;
      }
      android.os.IInterface iin = obj.queryLocalInterface(DESCRIPTOR);
      if (((iin!=null)&&(iin instanceof android.os.IServiceManager))) {
        return ((android.os.IServiceManager)iin); // 如果是同进程，返回 Binder 对象
      }
      return new android.os.IServiceManager.Stub.Proxy(obj); // 不是同进程，返回 Proxy 对象
    }
    @Override public android.os.IBinder asBinder()
    {
      return this;
    }
    /** @hide */
    public static java.lang.String getDefaultTransactionName(int transactionCode)
    {
      switch (transactionCode)
      {
        case TRANSACTION_getService:
        {
          return "getService";
        }
        case TRANSACTION_checkService:
        {
          return "checkService";
        }
        case TRANSACTION_addService:
        {
          return "addService";
        }
        case TRANSACTION_listServices:
        {
          return "listServices";
        }
        case TRANSACTION_registerForNotifications:
        {
          return "registerForNotifications";
        }
        case TRANSACTION_unregisterForNotifications:
        {
          return "unregisterForNotifications";
        }
        case TRANSACTION_isDeclared:
        {
          return "isDeclared";
        }
        case TRANSACTION_getDeclaredInstances:
        {
          return "getDeclaredInstances";
        }
        case TRANSACTION_updatableViaApex:
        {
          return "updatableViaApex";
        }
        case TRANSACTION_getConnectionInfo:
        {
          return "getConnectionInfo";
        }
        case TRANSACTION_registerClientCallback:
        {
          return "registerClientCallback";
        }
        case TRANSACTION_tryUnregisterService:
        {
          return "tryUnregisterService";
        }
        case TRANSACTION_getServiceDebugInfo:
        {
          return "getServiceDebugInfo";
        }
        default:
        {
          return null;
        }
      }
    }
    /** @hide */
    public java.lang.String getTransactionName(int transactionCode)
    {
      return this.getDefaultTransactionName(transactionCode);
    }
    @Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
    {
      java.lang.String descriptor = DESCRIPTOR;
      if (code >= android.os.IBinder.FIRST_CALL_TRANSACTION && code <= android.os.IBinder.LAST_CALL_TRANSACTION) {
        data.enforceInterface(descriptor);
      }
      switch (code)
      {
        case INTERFACE_TRANSACTION:
        {
          reply.writeString(descriptor);
          return true;
        }
      }
      switch (code)
      {
        case TRANSACTION_getService:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          data.enforceNoDataAvail();
          android.os.IBinder _result = this.getService(_arg0);
          reply.writeNoException();
          reply.writeStrongBinder(_result);
          break;
        }
        case TRANSACTION_checkService:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          data.enforceNoDataAvail();
          android.os.IBinder _result = this.checkService(_arg0);
          reply.writeNoException();
          reply.writeStrongBinder(_result);
          break;
        }
        case TRANSACTION_addService:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          android.os.IBinder _arg1;
          _arg1 = data.readStrongBinder();
          boolean _arg2;
          _arg2 = data.readBoolean();
          int _arg3;
          _arg3 = data.readInt();
          data.enforceNoDataAvail();
          this.addService(_arg0, _arg1, _arg2, _arg3);
          reply.writeNoException();
          break;
        }
        case TRANSACTION_listServices:
        {
          int _arg0;
          _arg0 = data.readInt();
          data.enforceNoDataAvail();
          java.lang.String[] _result = this.listServices(_arg0);
          reply.writeNoException();
          reply.writeStringArray(_result);
          break;
        }
        case TRANSACTION_registerForNotifications:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          android.os.IServiceCallback _arg1;
          _arg1 = android.os.IServiceCallback.Stub.asInterface(data.readStrongBinder());
          data.enforceNoDataAvail();
          this.registerForNotifications(_arg0, _arg1);
          reply.writeNoException();
          break;
        }
        case TRANSACTION_unregisterForNotifications:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          android.os.IServiceCallback _arg1;
          _arg1 = android.os.IServiceCallback.Stub.asInterface(data.readStrongBinder());
          data.enforceNoDataAvail();
          this.unregisterForNotifications(_arg0, _arg1);
          reply.writeNoException();
          break;
        }
        case TRANSACTION_isDeclared:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          data.enforceNoDataAvail();
          boolean _result = this.isDeclared(_arg0);
          reply.writeNoException();
          reply.writeBoolean(_result);
          break;
        }
        case TRANSACTION_getDeclaredInstances:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          data.enforceNoDataAvail();
          java.lang.String[] _result = this.getDeclaredInstances(_arg0);
          reply.writeNoException();
          reply.writeStringArray(_result);
          break;
        }
        case TRANSACTION_updatableViaApex:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          data.enforceNoDataAvail();
          java.lang.String _result = this.updatableViaApex(_arg0);
          reply.writeNoException();
          reply.writeString(_result);
          break;
        }
        case TRANSACTION_getConnectionInfo:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          data.enforceNoDataAvail();
          android.os.ConnectionInfo _result = this.getConnectionInfo(_arg0);
          reply.writeNoException();
          reply.writeTypedObject(_result, android.os.Parcelable.PARCELABLE_WRITE_RETURN_VALUE);
          break;
        }
        case TRANSACTION_registerClientCallback:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          android.os.IBinder _arg1;
          _arg1 = data.readStrongBinder();
          android.os.IClientCallback _arg2;
          _arg2 = android.os.IClientCallback.Stub.asInterface(data.readStrongBinder());
          data.enforceNoDataAvail();
          this.registerClientCallback(_arg0, _arg1, _arg2);
          reply.writeNoException();
          break;
        }
        case TRANSACTION_tryUnregisterService:
        {
          java.lang.String _arg0;
          _arg0 = data.readString();
          android.os.IBinder _arg1;
          _arg1 = data.readStrongBinder();
          data.enforceNoDataAvail();
          this.tryUnregisterService(_arg0, _arg1);
          reply.writeNoException();
          break;
        }
        case TRANSACTION_getServiceDebugInfo:
        {
          android.os.ServiceDebugInfo[] _result = this.getServiceDebugInfo();
          reply.writeNoException();
          reply.writeTypedArray(_result, android.os.Parcelable.PARCELABLE_WRITE_RETURN_VALUE);
          break;
        }
        default:
        {
          return super.onTransact(code, data, reply, flags);
        }
      }
      return true;
    }
    private static class Proxy implements android.os.IServiceManager
    {
      private android.os.IBinder mRemote;
      Proxy(android.os.IBinder remote)
      {
        mRemote = remote;
      }
      @Override public android.os.IBinder asBinder()
      {
        return mRemote;
      }
      public java.lang.String getInterfaceDescriptor()
      {
        return DESCRIPTOR;
      }
      /**
       * Retrieve an existing service called @a name from the
       * service manager.
       * 
       * This is the same as checkService (returns immediately) but
       * exists for legacy purposes.
       * 
       * Returns null if the service does not exist.
       */
      @Override public android.os.IBinder getService(java.lang.String name) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        android.os.IBinder _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          boolean _status = mRemote.transact(Stub.TRANSACTION_getService, _data, _reply, 0);
          _reply.readException();
          _result = _reply.readStrongBinder();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      /**
       * Retrieve an existing service called @a name from the service
       * manager. Non-blocking. Returns null if the service does not
       * exist.
       */
      @Override public android.os.IBinder checkService(java.lang.String name) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        android.os.IBinder _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          boolean _status = mRemote.transact(Stub.TRANSACTION_checkService, _data, _reply, 0);
          _reply.readException();
          _result = _reply.readStrongBinder();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      /**
       * Place a new @a service called @a name into the service
       * manager.
       */
      @Override public void addService(java.lang.String name, android.os.IBinder service, boolean allowIsolated, int dumpPriority) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          _data.writeStrongBinder(service);
          _data.writeBoolean(allowIsolated);
          _data.writeInt(dumpPriority);
          boolean _status = mRemote.transact(Stub.TRANSACTION_addService, _data, _reply, 0);
          _reply.readException();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
      }
      /** Return a list of all currently running services. */
      @Override public java.lang.String[] listServices(int dumpPriority) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        java.lang.String[] _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeInt(dumpPriority);
          boolean _status = mRemote.transact(Stub.TRANSACTION_listServices, _data, _reply, 0);
          _reply.readException();
          _result = _reply.createStringArray();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      /** Request a callback when a service is registered. */
      @Override public void registerForNotifications(java.lang.String name, android.os.IServiceCallback callback) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          _data.writeStrongInterface(callback);
          boolean _status = mRemote.transact(Stub.TRANSACTION_registerForNotifications, _data, _reply, 0);
          _reply.readException();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
      }
      /** Unregisters all requests for notifications for a specific callback. */
      @Override public void unregisterForNotifications(java.lang.String name, android.os.IServiceCallback callback) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          _data.writeStrongInterface(callback);
          boolean _status = mRemote.transact(Stub.TRANSACTION_unregisterForNotifications, _data, _reply, 0);
          _reply.readException();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
      }
      /**
       * Returns whether a given interface is declared on the device, even if it
       * is not started yet. For instance, this could be a service declared in the VINTF
       * manifest.
       */
      @Override public boolean isDeclared(java.lang.String name) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        boolean _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          boolean _status = mRemote.transact(Stub.TRANSACTION_isDeclared, _data, _reply, 0);
          _reply.readException();
          _result = _reply.readBoolean();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      /**
       * Returns all declared instances for a particular interface.
       * 
       * For instance, if 'android.foo.IFoo/foo' is declared, and 'android.foo.IFoo' is
       * passed here, then ["foo"] would be returned.
       */
      @Override public java.lang.String[] getDeclaredInstances(java.lang.String iface) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        java.lang.String[] _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(iface);
          boolean _status = mRemote.transact(Stub.TRANSACTION_getDeclaredInstances, _data, _reply, 0);
          _reply.readException();
          _result = _reply.createStringArray();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      /** If updatable-via-apex, returns the APEX via which this is updated. */
      @Override public java.lang.String updatableViaApex(java.lang.String name) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        java.lang.String _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          boolean _status = mRemote.transact(Stub.TRANSACTION_updatableViaApex, _data, _reply, 0);
          _reply.readException();
          _result = _reply.readString();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      /** If connection info is available for the given instance, returns the ConnectionInfo */
      @Override public android.os.ConnectionInfo getConnectionInfo(java.lang.String name) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        android.os.ConnectionInfo _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          boolean _status = mRemote.transact(Stub.TRANSACTION_getConnectionInfo, _data, _reply, 0);
          _reply.readException();
          _result = _reply.readTypedObject(android.os.ConnectionInfo.CREATOR);
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      /**
       * Request a callback when the number of clients of the service changes.
       * Used by LazyServiceRegistrar to dynamically stop services that have no clients.
       */
      @Override public void registerClientCallback(java.lang.String name, android.os.IBinder service, android.os.IClientCallback callback) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          _data.writeStrongBinder(service);
          _data.writeStrongInterface(callback);
          boolean _status = mRemote.transact(Stub.TRANSACTION_registerClientCallback, _data, _reply, 0);
          _reply.readException();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
      }
      /** Attempt to unregister and remove a service. Will fail if the service is still in use. */
      @Override public void tryUnregisterService(java.lang.String name, android.os.IBinder service) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeString(name);
          _data.writeStrongBinder(service);
          boolean _status = mRemote.transact(Stub.TRANSACTION_tryUnregisterService, _data, _reply, 0);
          _reply.readException();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
      }
      /** Get debug information for all currently registered services. */
      @Override public android.os.ServiceDebugInfo[] getServiceDebugInfo() throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain();
        android.os.Parcel _reply = android.os.Parcel.obtain();
        android.os.ServiceDebugInfo[] _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          boolean _status = mRemote.transact(Stub.TRANSACTION_getServiceDebugInfo, _data, _reply, 0);
          _reply.readException();
          _result = _reply.createTypedArray(android.os.ServiceDebugInfo.CREATOR);
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
    }
    static final int TRANSACTION_getService = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
    static final int TRANSACTION_checkService = (android.os.IBinder.FIRST_CALL_TRANSACTION + 1);
    static final int TRANSACTION_addService = (android.os.IBinder.FIRST_CALL_TRANSACTION + 2);
    static final int TRANSACTION_listServices = (android.os.IBinder.FIRST_CALL_TRANSACTION + 3);
    static final int TRANSACTION_registerForNotifications = (android.os.IBinder.FIRST_CALL_TRANSACTION + 4);
    static final int TRANSACTION_unregisterForNotifications = (android.os.IBinder.FIRST_CALL_TRANSACTION + 5);
    static final int TRANSACTION_isDeclared = (android.os.IBinder.FIRST_CALL_TRANSACTION + 6);
    static final int TRANSACTION_getDeclaredInstances = (android.os.IBinder.FIRST_CALL_TRANSACTION + 7);
    static final int TRANSACTION_updatableViaApex = (android.os.IBinder.FIRST_CALL_TRANSACTION + 8);
    static final int TRANSACTION_getConnectionInfo = (android.os.IBinder.FIRST_CALL_TRANSACTION + 9);
    static final int TRANSACTION_registerClientCallback = (android.os.IBinder.FIRST_CALL_TRANSACTION + 10);
    static final int TRANSACTION_tryUnregisterService = (android.os.IBinder.FIRST_CALL_TRANSACTION + 11);
    static final int TRANSACTION_getServiceDebugInfo = (android.os.IBinder.FIRST_CALL_TRANSACTION + 12);
    /** @hide */
    public int getMaxTransactionId()
    {
      return 12;
    }
  }
  public static final java.lang.String DESCRIPTOR = "android.os.IServiceManager";
  /* Must update values in IServiceManager.h */
  /** Allows services to dump sections according to priorities. */
  public static final int DUMP_FLAG_PRIORITY_CRITICAL = 1;
  public static final int DUMP_FLAG_PRIORITY_HIGH = 2;
  public static final int DUMP_FLAG_PRIORITY_NORMAL = 4;
  /**
   * Services are by default registered with a DEFAULT dump priority. DEFAULT priority has the
   * same priority as NORMAL priority but the services are not called with dump priority
   * arguments.
   */
  public static final int DUMP_FLAG_PRIORITY_DEFAULT = 8;
  public static final int DUMP_FLAG_PRIORITY_ALL = 15;
  /** Allows services to dump sections in protobuf format. */
  public static final int DUMP_FLAG_PROTO = 16;
  /**
   * Retrieve an existing service called @a name from the
   * service manager.
   * 
   * This is the same as checkService (returns immediately) but
   * exists for legacy purposes.
   * 
   * Returns null if the service does not exist.
   */
  @android.compat.annotation.UnsupportedAppUsage(overrideSourcePosition="frameworks/native/libs/binder/aidl/android/os/IServiceManager.aidl:63:1:63:25")
  public android.os.IBinder getService(java.lang.String name) throws android.os.RemoteException;
  /**
   * Retrieve an existing service called @a name from the service
   * manager. Non-blocking. Returns null if the service does not
   * exist.
   */
  @android.compat.annotation.UnsupportedAppUsage(overrideSourcePosition="frameworks/native/libs/binder/aidl/android/os/IServiceManager.aidl:71:1:71:25")
  public android.os.IBinder checkService(java.lang.String name) throws android.os.RemoteException;
  /**
   * Place a new @a service called @a name into the service
   * manager.
   */
  public void addService(java.lang.String name, android.os.IBinder service, boolean allowIsolated, int dumpPriority) throws android.os.RemoteException;
  /** Return a list of all currently running services. */
  public java.lang.String[] listServices(int dumpPriority) throws android.os.RemoteException;
  /** Request a callback when a service is registered. */
  public void registerForNotifications(java.lang.String name, android.os.IServiceCallback callback) throws android.os.RemoteException;
  /** Unregisters all requests for notifications for a specific callback. */
  public void unregisterForNotifications(java.lang.String name, android.os.IServiceCallback callback) throws android.os.RemoteException;
  /**
   * Returns whether a given interface is declared on the device, even if it
   * is not started yet. For instance, this could be a service declared in the VINTF
   * manifest.
   */
  public boolean isDeclared(java.lang.String name) throws android.os.RemoteException;
  /**
   * Returns all declared instances for a particular interface.
   * 
   * For instance, if 'android.foo.IFoo/foo' is declared, and 'android.foo.IFoo' is
   * passed here, then ["foo"] would be returned.
   */
  public java.lang.String[] getDeclaredInstances(java.lang.String iface) throws android.os.RemoteException;
  /** If updatable-via-apex, returns the APEX via which this is updated. */
  public java.lang.String updatableViaApex(java.lang.String name) throws android.os.RemoteException;
  /** If connection info is available for the given instance, returns the ConnectionInfo */
  public android.os.ConnectionInfo getConnectionInfo(java.lang.String name) throws android.os.RemoteException;
  /**
   * Request a callback when the number of clients of the service changes.
   * Used by LazyServiceRegistrar to dynamically stop services that have no clients.
   */
  public void registerClientCallback(java.lang.String name, android.os.IBinder service, android.os.IClientCallback callback) throws android.os.RemoteException;
  /** Attempt to unregister and remove a service. Will fail if the service is still in use. */
  public void tryUnregisterService(java.lang.String name, android.os.IBinder service) throws android.os.RemoteException;
  /** Get debug information for all currently registered services. */
  public android.os.ServiceDebugInfo[] getServiceDebugInfo() throws android.os.RemoteException;
}