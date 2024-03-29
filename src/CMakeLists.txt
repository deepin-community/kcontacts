add_library(KF5Contacts)
add_library(KF5::Contacts ALIAS KF5Contacts)

target_sources(KF5Contacts PRIVATE
    address.cpp
    addressee.cpp
    addressee.h
    addresseehelper.cpp
    addresseehelper.h
    addresseelist.h
    addressformat.cpp
    addressformatparser.cpp
    addressformatscript.cpp
    addressformatter.cpp
    address.h
    calendarurl.cpp
    calendarurl.h
    clientpidmap.cpp
    clientpidmap.h
    contactgroup.cpp
    contactgroup.h
    contactgrouptool.cpp
    contactgrouptool.h
    converter/ldifconverter.cpp
    converter/ldifconverter.h
    converter/vcardconverter.cpp
    converter/vcardconverter.h
    email.cpp
    email.h
    field.cpp
    fieldgroup.cpp
    fieldgroup.h
    field.h
    gender.cpp
    gender.h
    geo.cpp
    geo.h
    impp.cpp
    impp.h
    key.cpp
    key.h
    lang.cpp
    lang.h
    ldif.cpp
    ldif_p.h
    namespace.cpp
    nickname.cpp
    nickname.h
    note.cpp
    note.h
    org.cpp
    org.h
    parametermap_p.h
    phonenumber.cpp
    phonenumber.h
    picture.cpp
    picture.h
    related.cpp
    related.h
    resourcelocatorurl.cpp
    resourcelocatorurl.h
    role.cpp
    role.h
    secrecy.cpp
    secrecy.h
    sound.cpp
    sound.h
    timezone.cpp
    timezone.h
    title.cpp
    title.h
    vcarddrag.cpp
    vcarddrag.h
    vcardparser/vcard.cpp
    vcardparser/vcardline.cpp
    vcardparser/vcardline_p.h
    vcardparser/vcardparser.cpp
    vcardparser/vcardparser_p.h
    vcardparser/vcard_p.h
    vcardtool.cpp
    vcardtool_p.h


  kcontacts.qrc
  improtocols/improtocols.qrc
)

ecm_qt_declare_logging_category(KF5Contacts
    HEADER kcontacts_debug.h
    IDENTIFIER KCONTACTS_LOG
    CATEGORY_NAME kf.contacts
    OLD_CATEGORY_NAMES log_kcontacts org.kde.pim.kcontacts
    DESCRIPTION "KContacts"
    EXPORT KCONTACTS
)

ecm_generate_export_header(KF5Contacts
    EXPORT_FILE_NAME kcontacts_export.h
    BASE_NAME kcontacts
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS 5.88 5.89 5.92
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

target_include_directories(KF5Contacts INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KContacts>")
set(KContacts_BUILD_INCLUDE_DIRS
    ${KContacts_SOURCE_DIR}/src
    ${KContacts_BINARY_DIR}/src
    ${KContacts_SOURCE_DIR}/src/vcardparser
)
target_include_directories(KF5Contacts PUBLIC "$<BUILD_INTERFACE:${KContacts_BUILD_INCLUDE_DIRS}>")

target_link_libraries(KF5Contacts
PUBLIC
    Qt${QT_MAJOR_VERSION}::Core
    Qt${QT_MAJOR_VERSION}::Gui
PRIVATE
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::I18n
    KF5::I18nLocaleData
    KF5::Codecs # for the vcard parser
)

if (TARGET Qt6::Core5Compat)
    target_link_libraries(KF5Contacts PRIVATE Qt6::Core5Compat) # QTextCodec
endif()

set_target_properties(KF5Contacts PROPERTIES
    VERSION ${KContacts_VERSION}
    SOVERSION ${KContacts_SOVERSION}
    EXPORT_NAME Contacts
)

install(TARGETS KF5Contacts EXPORT KF5ContactsTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(KContacts_CamelCase_HEADERS
  HEADER_NAMES
  Address
  AddressFormat
  Addressee
  AddresseeList
  CalendarUrl
  ContactGroup
  ContactGroupTool
  Email
  Field
  Geo
  Gender
  Key
  Lang
  Namespace
  Impp
  PhoneNumber
  Picture
  Related
  ResourceLocatorUrl
  Secrecy
  Sound
  TimeZone
  Title
  Role
  Note
  Org
  NickName
  VCardDrag
  FieldGroup
  ClientPidMap
  PREFIX KContacts
  REQUIRED_HEADERS KContacts_HEADERS
)

add_subdirectory(converter)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/kcontacts_export.h
    ${KContacts_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KContacts/kcontacts
    COMPONENT Devel
)

install(FILES
    ${KContacts_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KContacts/KContacts
    COMPONENT Devel
)

ecm_qt_install_logging_categories(
    EXPORT KCONTACTS
    FILE kcontacts.categories
    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
)

ecm_generate_pri_file(BASE_NAME KContacts LIB_NAME KF5Contacts DEPS "KCoreAddons" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/KContacts)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if(BUILD_QCH)
    ecm_add_qch(
        KF5Contacts_QCH
        NAME KContacts
        BASE_NAME KF5Contacts
        VERSION ${KContacts_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${KContacts_HEADERS}
            "${CMAKE_SOURCE_DIR}/docs/AddressFormat.md"
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        LINK_QCHS
            Qt5Core_QCH
        INCLUDE_DIRS
            ${KContacts_BUILD_INCLUDE_DIRS}
        BLANK_MACROS
            KCONTACTS_EXPORT
            "KCONTACTS_DEPRECATED_VERSION(x, y, t)"
            "KCONTACTS_DEPRECATED_VERSION_BELATED(x, y, xt, yt, t)"
            "KCONTACTS_ENUMERATOR_DEPRECATED_VERSION(x, y, t)"
            "KCONTACTS_ENUMERATOR_DEPRECATED_VERSION_BELATED(x, y, xt, yt, t)"
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
