lessThan(QT_MAJOR_VERSION, 5) | lessThan(QT_MINOR_VERSION, 5) {
    message("Cannot build CanSocket-Qt-lib sources with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.5.0.")
}

requires(linux)
load(configure)
qtCompileTest(isotp)
load(qt_parts)
