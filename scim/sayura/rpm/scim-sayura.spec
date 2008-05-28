Name:		scim-sayura
Version:	0.3.3
Release:	1
Summary:	Sayura Sinhala input method for SCIM
Group:		System Environment/Libraries
License:	GPLv2
URL:		http://www.sayura.net/im/

Source:		%{name}-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires:	scim-devel
Requires:	scim
%description
This package provides the Sayura Sinhala input method for SCIM.

%prep
%setup -q %{name}-%{version}

%build
%configure --disable-static
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
rm $RPM_BUILD_ROOT%{_libdir}/scim-1.0/*/*/*.la

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root, -)
%doc README AUTHORS COPYING
%{_libdir}/scim-1.0/*/IMEngine/sayura.so
%{_datadir}/scim/icons/scim-sayura.png

%changelog
- Intuitive behaviour of al kireema after vowels and modifiers
- Allow typing rakaransaya or yansaya after a modifier
* Mon May 26 2008 Anuradha Ratnaweera <anuradha@taprobane.org> - 0.3.3-1
- Initial RPM packaging
