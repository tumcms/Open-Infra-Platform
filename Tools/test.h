/*
    Copyright (c) 2018 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

template <int N = 802> struct unrolled_dynamic_visitor {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		std::cout << N << std::endl;
		unrolled_dynamic_visitor<802>::castAndCall(ptr, f);
	}
};


template <> struct unrolled_dynamic_visitor<802> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(802)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(802) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(802)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<801>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<801> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(801)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(801) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(801)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<800>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<800> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(800)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(800) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(800)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<799>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<799> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(799)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(799) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(799)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<798>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<798> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(798)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(798) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(798)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<797>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<797> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(797)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(797) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(797)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<796>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<796> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(796)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(796) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(796)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<795>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<795> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(795)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(795) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(795)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<794>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<794> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(794)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(794) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(794)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<793>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<793> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(793)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(793) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(793)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<792>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<792> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(792)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(792) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(792)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<791>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<791> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(791)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(791) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(791)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<790>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<790> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(790)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(790) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(790)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<789>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<789> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(789)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(789) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(789)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<788>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<788> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(788)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(788) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(788)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<787>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<787> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(787)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(787) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(787)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<786>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<786> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(786)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(786) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(786)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<785>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<785> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(785)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(785) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(785)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<784>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<784> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(784)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(784) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(784)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<783>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<783> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(783)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(783) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(783)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<782>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<782> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(782)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(782) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(782)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<781>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<781> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(781)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(781) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(781)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<780>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<780> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(780)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(780) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(780)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<779>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<779> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(779)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(779) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(779)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<778>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<778> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(778)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(778) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(778)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<777>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<777> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(777)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(777) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(777)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<776>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<776> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(776)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(776) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(776)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<775>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<775> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(775)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(775) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(775)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<774>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<774> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(774)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(774) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(774)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<773>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<773> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(773)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(773) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(773)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<772>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<772> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(772)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(772) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(772)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<771>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<771> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(771)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(771) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(771)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<770>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<770> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(770)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(770) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(770)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<769>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<769> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(769)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(769) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(769)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<768>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<768> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(768)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(768) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(768)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<767>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<767> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(767)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(767) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(767)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<766>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<766> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(766)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(766) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(766)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<765>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<765> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(765)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(765) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(765)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<764>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<764> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(764)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(764) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(764)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<763>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<763> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(763)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(763) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(763)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<762>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<762> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(762)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(762) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(762)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<761>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<761> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(761)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(761) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(761)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<760>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<760> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(760)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(760) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(760)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<759>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<759> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(759)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(759) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(759)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<758>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<758> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(758)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(758) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(758)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<757>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<757> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(757)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(757) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(757)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<756>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<756> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(756)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(756) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(756)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<755>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<755> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(755)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(755) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(755)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<754>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<754> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(754)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(754) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(754)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<753>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<753> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(753)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(753) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(753)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<752>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<752> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(752)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(752) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(752)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<751>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<751> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(751)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(751) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(751)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<750>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<750> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(750)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(750) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(750)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<749>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<749> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(749)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(749) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(749)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<748>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<748> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(748)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(748) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(748)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<747>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<747> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(747)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(747) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(747)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<746>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<746> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(746)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(746) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(746)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<745>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<745> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(745)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(745) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(745)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<744>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<744> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(744)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(744) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(744)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<743>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<743> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(743)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(743) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(743)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<742>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<742> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(742)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(742) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(742)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<741>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<741> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(741)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(741) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(741)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<740>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<740> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(740)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(740) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(740)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<739>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<739> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(739)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(739) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(739)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<738>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<738> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(738)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(738) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(738)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<737>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<737> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(737)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(737) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(737)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<736>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<736> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(736)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(736) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(736)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<735>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<735> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(735)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(735) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(735)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<734>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<734> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(734)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(734) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(734)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<733>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<733> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(733)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(733) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(733)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<732>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<732> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(732)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(732) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(732)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<731>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<731> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(731)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(731) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(731)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<730>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<730> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(730)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(730) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(730)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<729>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<729> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(729)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(729) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(729)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<728>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<728> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(728)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(728) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(728)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<727>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<727> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(727)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(727) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(727)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<726>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<726> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(726)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(726) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(726)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<725>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<725> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(725)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(725) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(725)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<724>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<724> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(724)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(724) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(724)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<723>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<723> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(723)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(723) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(723)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<722>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<722> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(722)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(722) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(722)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<721>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<721> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(721)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(721) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(721)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<720>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<720> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(720)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(720) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(720)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<719>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<719> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(719)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(719) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(719)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<718>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<718> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(718)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(718) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(718)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<717>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<717> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(717)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(717) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(717)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<716>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<716> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(716)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(716) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(716)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<715>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<715> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(715)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(715) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(715)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<714>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<714> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(714)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(714) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(714)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<713>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<713> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(713)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(713) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(713)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<712>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<712> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(712)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(712) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(712)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<711>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<711> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(711)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(711) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(711)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<710>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<710> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(710)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(710) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(710)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<709>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<709> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(709)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(709) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(709)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<708>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<708> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(708)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(708) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(708)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<707>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<707> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(707)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(707) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(707)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<706>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<706> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(706)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(706) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(706)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<705>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<705> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(705)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(705) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(705)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<704>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<704> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(704)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(704) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(704)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<703>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<703> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(703)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(703) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(703)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<702>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<702> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(702)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(702) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(702)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<701>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<701> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(701)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(701) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(701)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<700>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<700> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(700)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(700) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(700)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<699>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<699> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(699)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(699) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(699)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<698>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<698> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(698)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(698) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(698)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<697>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<697> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(697)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(697) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(697)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<696>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<696> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(696)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(696) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(696)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<695>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<695> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(695)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(695) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(695)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<694>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<694> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(694)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(694) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(694)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<693>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<693> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(693)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(693) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(693)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<692>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<692> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(692)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(692) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(692)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<691>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<691> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(691)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(691) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(691)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<690>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<690> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(690)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(690) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(690)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<689>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<689> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(689)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(689) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(689)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<688>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<688> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(688)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(688) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(688)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<687>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<687> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(687)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(687) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(687)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<686>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<686> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(686)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(686) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(686)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<685>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<685> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(685)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(685) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(685)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<684>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<684> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(684)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(684) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(684)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<683>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<683> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(683)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(683) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(683)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<682>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<682> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(682)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(682) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(682)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<681>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<681> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(681)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(681) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(681)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<680>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<680> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(680)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(680) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(680)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<679>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<679> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(679)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(679) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(679)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<678>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<678> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(678)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(678) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(678)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<677>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<677> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(677)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(677) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(677)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<676>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<676> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(676)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(676) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(676)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<675>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<675> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(675)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(675) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(675)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<674>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<674> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(674)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(674) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(674)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<673>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<673> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(673)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(673) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(673)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<672>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<672> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(672)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(672) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(672)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<671>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<671> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(671)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(671) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(671)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<670>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<670> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(670)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(670) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(670)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<669>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<669> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(669)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(669) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(669)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<668>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<668> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(668)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(668) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(668)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<667>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<667> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(667)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(667) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(667)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<666>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<666> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(666)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(666) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(666)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<665>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<665> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(665)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(665) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(665)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<664>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<664> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(664)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(664) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(664)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<663>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<663> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(663)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(663) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(663)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<662>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<662> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(662)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(662) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(662)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<661>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<661> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(661)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(661) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(661)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<660>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<660> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(660)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(660) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(660)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<659>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<659> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(659)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(659) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(659)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<658>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<658> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(658)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(658) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(658)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<657>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<657> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(657)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(657) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(657)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<656>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<656> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(656)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(656) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(656)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<655>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<655> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(655)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(655) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(655)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<654>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<654> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(654)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(654) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(654)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<653>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<653> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(653)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(653) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(653)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<652>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<652> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(652)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(652) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(652)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<651>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<651> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(651)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(651) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(651)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<650>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<650> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(650)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(650) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(650)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<649>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<649> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(649)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(649) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(649)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<648>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<648> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(648)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(648) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(648)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<647>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<647> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(647)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(647) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(647)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<646>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<646> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(646)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(646) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(646)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<645>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<645> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(645)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(645) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(645)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<644>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<644> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(644)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(644) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(644)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<643>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<643> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(643)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(643) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(643)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<642>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<642> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(642)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(642) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(642)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<641>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<641> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(641)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(641) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(641)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<640>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<640> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(640)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(640) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(640)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<639>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<639> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(639)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(639) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(639)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<638>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<638> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(638)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(638) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(638)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<637>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<637> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(637)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(637) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(637)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<636>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<636> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(636)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(636) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(636)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<635>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<635> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(635)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(635) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(635)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<634>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<634> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(634)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(634) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(634)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<633>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<633> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(633)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(633) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(633)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<632>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<632> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(632)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(632) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(632)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<631>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<631> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(631)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(631) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(631)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<630>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<630> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(630)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(630) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(630)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<629>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<629> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(629)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(629) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(629)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<628>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<628> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(628)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(628) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(628)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<627>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<627> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(627)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(627) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(627)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<626>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<626> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(626)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(626) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(626)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<625>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<625> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(625)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(625) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(625)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<624>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<624> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(624)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(624) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(624)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<623>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<623> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(623)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(623) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(623)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<622>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<622> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(622)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(622) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(622)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<621>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<621> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(621)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(621) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(621)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<620>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<620> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(620)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(620) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(620)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<619>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<619> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(619)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(619) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(619)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<618>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<618> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(618)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(618) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(618)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<617>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<617> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(617)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(617) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(617)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<616>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<616> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(616)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(616) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(616)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<615>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<615> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(615)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(615) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(615)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<614>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<614> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(614)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(614) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(614)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<613>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<613> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(613)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(613) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(613)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<612>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<612> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(612)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(612) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(612)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<611>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<611> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(611)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(611) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(611)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<610>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<610> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(610)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(610) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(610)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<609>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<609> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(609)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(609) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(609)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<608>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<608> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(608)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(608) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(608)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<607>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<607> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(607)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(607) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(607)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<606>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<606> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(606)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(606) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(606)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<605>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<605> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(605)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(605) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(605)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<604>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<604> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(604)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(604) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(604)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<603>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<603> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(603)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(603) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(603)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<602>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<602> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(602)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(602) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(602)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<601>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<601> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(601)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(601) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(601)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<600>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<600> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(600)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(600) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(600)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<599>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<599> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(599)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(599) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(599)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<598>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<598> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(598)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(598) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(598)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<597>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<597> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(597)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(597) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(597)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<596>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<596> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(596)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(596) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(596)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<595>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<595> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(595)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(595) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(595)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<594>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<594> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(594)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(594) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(594)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<593>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<593> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(593)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(593) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(593)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<592>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<592> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(592)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(592) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(592)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<591>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<591> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(591)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(591) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(591)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<590>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<590> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(590)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(590) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(590)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<589>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<589> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(589)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(589) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(589)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<588>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<588> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(588)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(588) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(588)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<587>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<587> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(587)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(587) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(587)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<586>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<586> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(586)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(586) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(586)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<585>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<585> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(585)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(585) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(585)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<584>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<584> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(584)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(584) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(584)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<583>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<583> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(583)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(583) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(583)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<582>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<582> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(582)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(582) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(582)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<581>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<581> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(581)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(581) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(581)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<580>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<580> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(580)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(580) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(580)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<579>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<579> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(579)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(579) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(579)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<578>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<578> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(578)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(578) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(578)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<577>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<577> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(577)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(577) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(577)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<576>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<576> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(576)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(576) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(576)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<575>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<575> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(575)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(575) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(575)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<574>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<574> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(574)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(574) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(574)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<573>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<573> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(573)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(573) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(573)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<572>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<572> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(572)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(572) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(572)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<571>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<571> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(571)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(571) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(571)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<570>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<570> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(570)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(570) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(570)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<569>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<569> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(569)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(569) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(569)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<568>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<568> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(568)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(568) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(568)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<567>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<567> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(567)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(567) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(567)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<566>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<566> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(566)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(566) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(566)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<565>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<565> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(565)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(565) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(565)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<564>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<564> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(564)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(564) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(564)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<563>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<563> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(563)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(563) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(563)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<562>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<562> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(562)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(562) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(562)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<561>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<561> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(561)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(561) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(561)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<560>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<560> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(560)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(560) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(560)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<559>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<559> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(559)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(559) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(559)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<558>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<558> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(558)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(558) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(558)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<557>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<557> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(557)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(557) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(557)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<556>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<556> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(556)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(556) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(556)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<555>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<555> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(555)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(555) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(555)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<554>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<554> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(554)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(554) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(554)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<553>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<553> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(553)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(553) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(553)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<552>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<552> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(552)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(552) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(552)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<551>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<551> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(551)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(551) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(551)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<550>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<550> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(550)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(550) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(550)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<549>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<549> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(549)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(549) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(549)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<548>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<548> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(548)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(548) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(548)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<547>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<547> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(547)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(547) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(547)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<546>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<546> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(546)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(546) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(546)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<545>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<545> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(545)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(545) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(545)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<544>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<544> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(544)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(544) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(544)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<543>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<543> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(543)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(543) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(543)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<542>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<542> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(542)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(542) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(542)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<541>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<541> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(541)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(541) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(541)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<540>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<540> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(540)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(540) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(540)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<539>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<539> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(539)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(539) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(539)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<538>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<538> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(538)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(538) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(538)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<537>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<537> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(537)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(537) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(537)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<536>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<536> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(536)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(536) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(536)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<535>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<535> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(535)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(535) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(535)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<534>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<534> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(534)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(534) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(534)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<533>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<533> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(533)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(533) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(533)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<532>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<532> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(532)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(532) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(532)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<531>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<531> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(531)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(531) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(531)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<530>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<530> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(530)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(530) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(530)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<529>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<529> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(529)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(529) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(529)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<528>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<528> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(528)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(528) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(528)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<527>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<527> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(527)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(527) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(527)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<526>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<526> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(526)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(526) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(526)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<525>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<525> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(525)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(525) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(525)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<524>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<524> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(524)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(524) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(524)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<523>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<523> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(523)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(523) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(523)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<522>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<522> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(522)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(522) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(522)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<521>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<521> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(521)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(521) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(521)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<520>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<520> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(520)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(520) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(520)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<519>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<519> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(519)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(519) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(519)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<518>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<518> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(518)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(518) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(518)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<517>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<517> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(517)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(517) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(517)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<516>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<516> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(516)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(516) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(516)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<515>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<515> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(515)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(515) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(515)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<514>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<514> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(514)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(514) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(514)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<513>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<513> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(513)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(513) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(513)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<512>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<512> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(512)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(512) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(512)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<511>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<511> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(511)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(511) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(511)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<510>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<510> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(510)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(510) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(510)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<509>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<509> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(509)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(509) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(509)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<508>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<508> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(508)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(508) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(508)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<507>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<507> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(507)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(507) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(507)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<506>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<506> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(506)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(506) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(506)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<505>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<505> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(505)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(505) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(505)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<504>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<504> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(504)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(504) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(504)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<503>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<503> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(503)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(503) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(503)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<502>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<502> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(502)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(502) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(502)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<501>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<501> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(501)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(501) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(501)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<500>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<500> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(500)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(500) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(500)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<499>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<499> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(499)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(499) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(499)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<498>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<498> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(498)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(498) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(498)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<497>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<497> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(497)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(497) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(497)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<496>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<496> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(496)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(496) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(496)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<495>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<495> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(495)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(495) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(495)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<494>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<494> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(494)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(494) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(494)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<493>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<493> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(493)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(493) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(493)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<492>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<492> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(492)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(492) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(492)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<491>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<491> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(491)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(491) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(491)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<490>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<490> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(490)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(490) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(490)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<489>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<489> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(489)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(489) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(489)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<488>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<488> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(488)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(488) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(488)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<487>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<487> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(487)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(487) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(487)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<486>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<486> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(486)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(486) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(486)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<485>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<485> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(485)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(485) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(485)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<484>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<484> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(484)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(484) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(484)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<483>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<483> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(483)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(483) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(483)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<482>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<482> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(482)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(482) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(482)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<481>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<481> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(481)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(481) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(481)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<480>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<480> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(480)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(480) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(480)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<479>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<479> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(479)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(479) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(479)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<478>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<478> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(478)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(478) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(478)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<477>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<477> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(477)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(477) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(477)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<476>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<476> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(476)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(476) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(476)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<475>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<475> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(475)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(475) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(475)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<474>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<474> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(474)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(474) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(474)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<473>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<473> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(473)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(473) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(473)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<472>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<472> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(472)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(472) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(472)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<471>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<471> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(471)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(471) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(471)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<470>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<470> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(470)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(470) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(470)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<469>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<469> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(469)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(469) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(469)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<468>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<468> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(468)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(468) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(468)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<467>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<467> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(467)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(467) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(467)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<466>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<466> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(466)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(466) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(466)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<465>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<465> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(465)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(465) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(465)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<464>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<464> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(464)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(464) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(464)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<463>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<463> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(463)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(463) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(463)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<462>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<462> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(462)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(462) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(462)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<461>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<461> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(461)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(461) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(461)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<460>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<460> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(460)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(460) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(460)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<459>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<459> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(459)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(459) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(459)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<458>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<458> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(458)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(458) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(458)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<457>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<457> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(457)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(457) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(457)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<456>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<456> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(456)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(456) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(456)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<455>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<455> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(455)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(455) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(455)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<454>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<454> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(454)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(454) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(454)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<453>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<453> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(453)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(453) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(453)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<452>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<452> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(452)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(452) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(452)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<451>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<451> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(451)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(451) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(451)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<450>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<450> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(450)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(450) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(450)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<449>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<449> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(449)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(449) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(449)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<448>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<448> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(448)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(448) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(448)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<447>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<447> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(447)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(447) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(447)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<446>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<446> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(446)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(446) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(446)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<445>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<445> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(445)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(445) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(445)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<444>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<444> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(444)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(444) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(444)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<443>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<443> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(443)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(443) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(443)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<442>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<442> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(442)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(442) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(442)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<441>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<441> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(441)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(441) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(441)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<440>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<440> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(440)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(440) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(440)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<439>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<439> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(439)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(439) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(439)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<438>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<438> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(438)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(438) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(438)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<437>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<437> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(437)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(437) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(437)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<436>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<436> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(436)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(436) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(436)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<435>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<435> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(435)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(435) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(435)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<434>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<434> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(434)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(434) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(434)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<433>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<433> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(433)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(433) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(433)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<432>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<432> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(432)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(432) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(432)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<431>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<431> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(431)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(431) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(431)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<430>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<430> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(430)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(430) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(430)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<429>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<429> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(429)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(429) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(429)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<428>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<428> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(428)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(428) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(428)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<427>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<427> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(427)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(427) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(427)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<426>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<426> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(426)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(426) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(426)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<425>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<425> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(425)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(425) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(425)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<424>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<424> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(424)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(424) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(424)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<423>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<423> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(423)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(423) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(423)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<422>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<422> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(422)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(422) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(422)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<421>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<421> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(421)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(421) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(421)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<420>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<420> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(420)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(420) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(420)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<419>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<419> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(419)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(419) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(419)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<418>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<418> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(418)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(418) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(418)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<417>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<417> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(417)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(417) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(417)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<416>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<416> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(416)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(416) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(416)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<415>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<415> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(415)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(415) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(415)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<414>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<414> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(414)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(414) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(414)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<413>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<413> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(413)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(413) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(413)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<412>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<412> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(412)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(412) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(412)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<411>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<411> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(411)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(411) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(411)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<410>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<410> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(410)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(410) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(410)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<409>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<409> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(409)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(409) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(409)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<408>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<408> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(408)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(408) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(408)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<407>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<407> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(407)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(407) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(407)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<406>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<406> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(406)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(406) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(406)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<405>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<405> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(405)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(405) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(405)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<404>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<404> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(404)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(404) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(404)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<403>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<403> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(403)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(403) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(403)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<402>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<402> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(402)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(402) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(402)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<401>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<401> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(401)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(401) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(401)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<400>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<400> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(400)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(400) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(400)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<399>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<399> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(399)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(399) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(399)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<398>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<398> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(398)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(398) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(398)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<397>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<397> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(397)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(397) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(397)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<396>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<396> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(396)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(396) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(396)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<395>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<395> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(395)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(395) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(395)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<394>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<394> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(394)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(394) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(394)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<393>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<393> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(393)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(393) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(393)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<392>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<392> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(392)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(392) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(392)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<391>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<391> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(391)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(391) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(391)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<390>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<390> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(390)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(390) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(390)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<389>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<389> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(389)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(389) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(389)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<388>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<388> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(388)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(388) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(388)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<387>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<387> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(387)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(387) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(387)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<386>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<386> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(386)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(386) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(386)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<385>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<385> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(385)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(385) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(385)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<384>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<384> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(384)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(384) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(384)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<383>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<383> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(383)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(383) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(383)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<382>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<382> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(382)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(382) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(382)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<381>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<381> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(381)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(381) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(381)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<380>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<380> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(380)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(380) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(380)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<379>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<379> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(379)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(379) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(379)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<378>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<378> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(378)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(378) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(378)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<377>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<377> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(377)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(377) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(377)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<376>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<376> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(376)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(376) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(376)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<375>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<375> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(375)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(375) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(375)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<374>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<374> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(374)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(374) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(374)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<373>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<373> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(373)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(373) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(373)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<372>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<372> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(372)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(372) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(372)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<371>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<371> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(371)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(371) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(371)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<370>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<370> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(370)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(370) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(370)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<369>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<369> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(369)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(369) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(369)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<368>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<368> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(368)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(368) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(368)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<367>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<367> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(367)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(367) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(367)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<366>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<366> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(366)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(366) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(366)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<365>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<365> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(365)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(365) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(365)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<364>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<364> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(364)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(364) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(364)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<363>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<363> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(363)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(363) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(363)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<362>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<362> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(362)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(362) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(362)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<361>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<361> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(361)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(361) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(361)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<360>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<360> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(360)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(360) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(360)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<359>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<359> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(359)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(359) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(359)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<358>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<358> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(358)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(358) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(358)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<357>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<357> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(357)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(357) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(357)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<356>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<356> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(356)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(356) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(356)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<355>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<355> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(355)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(355) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(355)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<354>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<354> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(354)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(354) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(354)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<353>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<353> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(353)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(353) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(353)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<352>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<352> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(352)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(352) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(352)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<351>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<351> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(351)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(351) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(351)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<350>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<350> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(350)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(350) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(350)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<349>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<349> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(349)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(349) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(349)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<348>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<348> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(348)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(348) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(348)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<347>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<347> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(347)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(347) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(347)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<346>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<346> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(346)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(346) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(346)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<345>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<345> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(345)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(345) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(345)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<344>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<344> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(344)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(344) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(344)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<343>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<343> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(343)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(343) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(343)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<342>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<342> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(342)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(342) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(342)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<341>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<341> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(341)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(341) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(341)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<340>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<340> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(340)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(340) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(340)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<339>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<339> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(339)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(339) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(339)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<338>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<338> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(338)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(338) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(338)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<337>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<337> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(337)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(337) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(337)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<336>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<336> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(336)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(336) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(336)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<335>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<335> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(335)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(335) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(335)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<334>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<334> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(334)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(334) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(334)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<333>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<333> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(333)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(333) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(333)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<332>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<332> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(332)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(332) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(332)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<331>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<331> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(331)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(331) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(331)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<330>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<330> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(330)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(330) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(330)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<329>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<329> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(329)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(329) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(329)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<328>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<328> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(328)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(328) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(328)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<327>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<327> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(327)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(327) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(327)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<326>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<326> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(326)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(326) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(326)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<325>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<325> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(325)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(325) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(325)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<324>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<324> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(324)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(324) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(324)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<323>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<323> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(323)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(323) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(323)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<322>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<322> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(322)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(322) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(322)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<321>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<321> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(321)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(321) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(321)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<320>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<320> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(320)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(320) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(320)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<319>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<319> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(319)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(319) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(319)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<318>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<318> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(318)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(318) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(318)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<317>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<317> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(317)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(317) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(317)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<316>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<316> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(316)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(316) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(316)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<315>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<315> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(315)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(315) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(315)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<314>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<314> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(314)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(314) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(314)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<313>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<313> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(313)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(313) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(313)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<312>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<312> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(312)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(312) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(312)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<311>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<311> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(311)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(311) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(311)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<310>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<310> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(310)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(310) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(310)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<309>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<309> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(309)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(309) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(309)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<308>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<308> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(308)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(308) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(308)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<307>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<307> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(307)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(307) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(307)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<306>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<306> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(306)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(306) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(306)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<305>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<305> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(305)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(305) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(305)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<304>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<304> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(304)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(304) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(304)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<303>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<303> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(303)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(303) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(303)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<302>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<302> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(302)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(302) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(302)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<301>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<301> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(301)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(301) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(301)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<300>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<300> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(300)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(300) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(300)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<299>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<299> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(299)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(299) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(299)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<298>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<298> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(298)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(298) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(298)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<297>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<297> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(297)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(297) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(297)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<296>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<296> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(296)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(296) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(296)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<295>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<295> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(295)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(295) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(295)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<294>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<294> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(294)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(294) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(294)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<293>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<293> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(293)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(293) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(293)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<292>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<292> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(292)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(292) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(292)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<291>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<291> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(291)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(291) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(291)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<290>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<290> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(290)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(290) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(290)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<289>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<289> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(289)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(289) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(289)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<288>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<288> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(288)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(288) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(288)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<287>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<287> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(287)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(287) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(287)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<286>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<286> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(286)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(286) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(286)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<285>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<285> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(285)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(285) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(285)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<284>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<284> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(284)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(284) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(284)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<283>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<283> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(283)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(283) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(283)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<282>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<282> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(282)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(282) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(282)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<281>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<281> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(281)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(281) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(281)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<280>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<280> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(280)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(280) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(280)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<279>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<279> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(279)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(279) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(279)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<278>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<278> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(278)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(278) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(278)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<277>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<277> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(277)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(277) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(277)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<276>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<276> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(276)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(276) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(276)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<275>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<275> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(275)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(275) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(275)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<274>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<274> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(274)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(274) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(274)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<273>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<273> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(273)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(273) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(273)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<272>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<272> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(272)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(272) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(272)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<271>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<271> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(271)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(271) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(271)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<270>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<270> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(270)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(270) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(270)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<269>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<269> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(269)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(269) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(269)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<268>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<268> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(268)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(268) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(268)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<267>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<267> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(267)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(267) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(267)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<266>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<266> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(266)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(266) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(266)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<265>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<265> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(265)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(265) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(265)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<264>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<264> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(264)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(264) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(264)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<263>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<263> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(263)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(263) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(263)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<262>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<262> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(262)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(262) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(262)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<261>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<261> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(261)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(261) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(261)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<260>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<260> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(260)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(260) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(260)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<259>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<259> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(259)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(259) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(259)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<258>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<258> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(258)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(258) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(258)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<257>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<257> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(257)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(257) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(257)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<256>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<256> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(256)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(256) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(256)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<255>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<255> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(255)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(255) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(255)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<254>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<254> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(254)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(254) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(254)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<253>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<253> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(253)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(253) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(253)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<252>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<252> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(252)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(252) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(252)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<251>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<251> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(251)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(251) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(251)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<250>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<250> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(250)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(250) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(250)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<249>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<249> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(249)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(249) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(249)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<248>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<248> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(248)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(248) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(248)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<247>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<247> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(247)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(247) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(247)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<246>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<246> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(246)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(246) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(246)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<245>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<245> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(245)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(245) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(245)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<244>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<244> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(244)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(244) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(244)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<243>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<243> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(243)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(243) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(243)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<242>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<242> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(242)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(242) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(242)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<241>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<241> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(241)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(241) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(241)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<240>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<240> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(240)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(240) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(240)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<239>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<239> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(239)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(239) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(239)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<238>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<238> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(238)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(238) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(238)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<237>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<237> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(237)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(237) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(237)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<236>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<236> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(236)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(236) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(236)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<235>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<235> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(235)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(235) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(235)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<234>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<234> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(234)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(234) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(234)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<233>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<233> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(233)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(233) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(233)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<232>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<232> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(232)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(232) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(232)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<231>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<231> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(231)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(231) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(231)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<230>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<230> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(230)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(230) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(230)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<229>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<229> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(229)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(229) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(229)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<228>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<228> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(228)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(228) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(228)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<227>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<227> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(227)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(227) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(227)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<226>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<226> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(226)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(226) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(226)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<225>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<225> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(225)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(225) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(225)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<224>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<224> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(224)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(224) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(224)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<223>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<223> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(223)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(223) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(223)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<222>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<222> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(222)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(222) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(222)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<221>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<221> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(221)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(221) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(221)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<220>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<220> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(220)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(220) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(220)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<219>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<219> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(219)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(219) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(219)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<218>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<218> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(218)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(218) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(218)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<217>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<217> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(217)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(217) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(217)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<216>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<216> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(216)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(216) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(216)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<215>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<215> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(215)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(215) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(215)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<214>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<214> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(214)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(214) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(214)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<213>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<213> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(213)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(213) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(213)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<212>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<212> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(212)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(212) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(212)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<211>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<211> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(211)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(211) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(211)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<210>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<210> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(210)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(210) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(210)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<209>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<209> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(209)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(209) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(209)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<208>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<208> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(208)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(208) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(208)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<207>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<207> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(207)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(207) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(207)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<206>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<206> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(206)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(206) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(206)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<205>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<205> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(205)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(205) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(205)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<204>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<204> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(204)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(204) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(204)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<203>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<203> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(203)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(203) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(203)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<202>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<202> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(202)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(202) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(202)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<201>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<201> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(201)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(201) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(201)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<200>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<200> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(200)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(200) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(200)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<199>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<199> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(199)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(199) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(199)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<198>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<198> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(198)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(198) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(198)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<197>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<197> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(197)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(197) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(197)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<196>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<196> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(196)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(196) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(196)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<195>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<195> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(195)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(195) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(195)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<194>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<194> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(194)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(194) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(194)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<193>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<193> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(193)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(193) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(193)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<192>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<192> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(192)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(192) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(192)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<191>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<191> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(191)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(191) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(191)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<190>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<190> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(190)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(190) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(190)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<189>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<189> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(189)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(189) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(189)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<188>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<188> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(188)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(188) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(188)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<187>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<187> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(187)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(187) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(187)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<186>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<186> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(186)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(186) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(186)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<185>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<185> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(185)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(185) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(185)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<184>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<184> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(184)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(184) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(184)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<183>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<183> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(183)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(183) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(183)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<182>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<182> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(182)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(182) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(182)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<181>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<181> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(181)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(181) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(181)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<180>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<180> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(180)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(180) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(180)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<179>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<179> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(179)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(179) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(179)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<178>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<178> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(178)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(178) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(178)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<177>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<177> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(177)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(177) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(177)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<176>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<176> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(176)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(176) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(176)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<175>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<175> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(175)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(175) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(175)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<174>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<174> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(174)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(174) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(174)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<173>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<173> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(173)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(173) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(173)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<172>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<172> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(172)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(172) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(172)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<171>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<171> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(171)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(171) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(171)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<170>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<170> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(170)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(170) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(170)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<169>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<169> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(169)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(169) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(169)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<168>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<168> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(168)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(168) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(168)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<167>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<167> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(167)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(167) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(167)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<166>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<166> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(166)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(166) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(166)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<165>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<165> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(165)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(165) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(165)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<164>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<164> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(164)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(164) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(164)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<163>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<163> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(163)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(163) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(163)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<162>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<162> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(162)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(162) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(162)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<161>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<161> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(161)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(161) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(161)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<160>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<160> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(160)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(160) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(160)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<159>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<159> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(159)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(159) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(159)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<158>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<158> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(158)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(158) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(158)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<157>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<157> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(157)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(157) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(157)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<156>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<156> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(156)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(156) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(156)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<155>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<155> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(155)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(155) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(155)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<154>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<154> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(154)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(154) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(154)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<153>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<153> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(153)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(153) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(153)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<152>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<152> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(152)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(152) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(152)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<151>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<151> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(151)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(151) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(151)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<150>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<150> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(150)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(150) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(150)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<149>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<149> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(149)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(149) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(149)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<148>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<148> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(148)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(148) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(148)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<147>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<147> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(147)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(147) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(147)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<146>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<146> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(146)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(146) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(146)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<145>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<145> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(145)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(145) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(145)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<144>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<144> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(144)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(144) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(144)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<143>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<143> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(143)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(143) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(143)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<142>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<142> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(142)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(142) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(142)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<141>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<141> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(141)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(141) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(141)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<140>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<140> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(140)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(140) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(140)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<139>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<139> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(139)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(139) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(139)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<138>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<138> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(138)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(138) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(138)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<137>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<137> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(137)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(137) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(137)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<136>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<136> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(136)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(136) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(136)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<135>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<135> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(135)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(135) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(135)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<134>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<134> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(134)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(134) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(134)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<133>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<133> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(133)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(133) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(133)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<132>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<132> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(132)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(132) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(132)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<131>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<131> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(131)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(131) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(131)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<130>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<130> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(130)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(130) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(130)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<129>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<129> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(129)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(129) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(129)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<128>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<128> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(128)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(128) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(128)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<127>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<127> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(127)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(127) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(127)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<126>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<126> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(126)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(126) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(126)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<125>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<125> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(125)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(125) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(125)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<124>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<124> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(124)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(124) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(124)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<123>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<123> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(123)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(123) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(123)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<122>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<122> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(122)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(122) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(122)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<121>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<121> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(121)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(121) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(121)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<120>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<120> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(120)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(120) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(120)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<119>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<119> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(119)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(119) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(119)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<118>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<118> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(118)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(118) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(118)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<117>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<117> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(117)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(117) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(117)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<116>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<116> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(116)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(116) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(116)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<115>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<115> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(115)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(115) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(115)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<114>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<114> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(114)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(114) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(114)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<113>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<113> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(113)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(113) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(113)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<112>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<112> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(112)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(112) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(112)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<111>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<111> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(111)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(111) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(111)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<110>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<110> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(110)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(110) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(110)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<109>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<109> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(109)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(109) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(109)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<108>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<108> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(108)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(108) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(108)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<107>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<107> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(107)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(107) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(107)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<106>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<106> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(106)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(106) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(106)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<105>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<105> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(105)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(105) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(105)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<104>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<104> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(104)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(104) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(104)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<103>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<103> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(103)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(103) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(103)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<102>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<102> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(102)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(102) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(102)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<101>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<101> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(101)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(101) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(101)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<100>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<100> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(100)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(100) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(100)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<99>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<99> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(99)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(99) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(99)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<98>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<98> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(98)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(98) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(98)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<97>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<97> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(97)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(97) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(97)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<96>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<96> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(96)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(96) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(96)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<95>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<95> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(95)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(95) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(95)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<94>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<94> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(94)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(94) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(94)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<93>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<93> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(93)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(93) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(93)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<92>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<92> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(92)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(92) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(92)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<91>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<91> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(91)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(91) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(91)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<90>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<90> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(90)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(90) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(90)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<89>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<89> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(89)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(89) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(89)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<88>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<88> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(88)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(88) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(88)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<87>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<87> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(87)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(87) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(87)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<86>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<86> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(86)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(86) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(86)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<85>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<85> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(85)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(85) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(85)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<84>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<84> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(84)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(84) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(84)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<83>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<83> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(83)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(83) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(83)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<82>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<82> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(82)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(82) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(82)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<81>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<81> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(81)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(81) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(81)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<80>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<80> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(80)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(80) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(80)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<79>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<79> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(79)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(79) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(79)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<78>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<78> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(78)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(78) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(78)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<77>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<77> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(77)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(77) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(77)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<76>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<76> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(76)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(76) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(76)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<75>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<75> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(75)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(75) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(75)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<74>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<74> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(74)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(74) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(74)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<73>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<73> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(73)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(73) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(73)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<72>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<72> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(72)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(72) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(72)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<71>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<71> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(71)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(71) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(71)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<70>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<70> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(70)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(70) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(70)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<69>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<69> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(69)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(69) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(69)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<68>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<68> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(68)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(68) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(68)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<67>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<67> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(67)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(67) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(67)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<66>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<66> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(66)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(66) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(66)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<65>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<65> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(65)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(65) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(65)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<64>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<64> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(64)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(64) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(64)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<63>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<63> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(63)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(63) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(63)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<62>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<62> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(62)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(62) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(62)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<61>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<61> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(61)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(61) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(61)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<60>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<60> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(60)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(60) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(60)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<59>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<59> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(59)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(59) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(59)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<58>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<58> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(58)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(58) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(58)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<57>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<57> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(57)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(57) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(57)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<56>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<56> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(56)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(56) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(56)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<55>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<55> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(55)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(55) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(55)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<54>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<54> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(54)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(54) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(54)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<53>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<53> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(53)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(53) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(53)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<52>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<52> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(52)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(52) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(52)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<51>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<51> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(51)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(51) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(51)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<50>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<50> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(50)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(50) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(50)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<49>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<49> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(49)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(49) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(49)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<48>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<48> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(48)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(48) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(48)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<47>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<47> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(47)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(47) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(47)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<46>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<46> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(46)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(46) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(46)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<45>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<45> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(45)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(45) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(45)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<44>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<44> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(44)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(44) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(44)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<43>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<43> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(43)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(43) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(43)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<42>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<42> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(42)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(42) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(42)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<41>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<41> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(41)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(41) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(41)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<40>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<40> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(40)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(40) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(40)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<39>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<39> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(39)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(39) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(39)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<38>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<38> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(38)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(38) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(38)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<37>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<37> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(37)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(37) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(37)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<36>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<36> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(36)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(36) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(36)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<35>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<35> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(35)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(35) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(35)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<34>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<34> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(34)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(34) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(34)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<33>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<33> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(33)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(33) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(33)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<32>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<32> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(32)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(32) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(32)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<31>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<31> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(31)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(31) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(31)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<30>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<30> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(30)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(30) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(30)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<29>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<29> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(29)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(29) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(29)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<28>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<28> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(28)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(28) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(28)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<27>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<27> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(27)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(27) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(27)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<26>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<26> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(26)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(26) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(26)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<25>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<25> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(25)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(25) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(25)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<24>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<24> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(24)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(24) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(24)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<23>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<23> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(23)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(23) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(23)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<22>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<22> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(22)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(22) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(22)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<21>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<21> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(21)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(21) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(21)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<20>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<20> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(20)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(20) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(20)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<19>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<19> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(19)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(19) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(19)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<18>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<18> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(18)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(18) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(18)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<17>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<17> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(17)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(17) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(17)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<16>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<16> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(16)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(16) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(16)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<15>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<15> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(15)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(15) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(15)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<14>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<14> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(14)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(14) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(14)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<13>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<13> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(13)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(13) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(13)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<12>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<12> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(12)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(12) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(12)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<11>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<11> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(11)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(11) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(11)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<10>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<10> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(10)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(10) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(10)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<9>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<9> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(9)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(9) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(9)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<8>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<8> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(8)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(8) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(8)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<7>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<7> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(7)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(7) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(7)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<6>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<6> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(6)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(6) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(6)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<5>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<5> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(5)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(5) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(5)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<4>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<4> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(4)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(4) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(4)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<3>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<3> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(3)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(3) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(3)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<2>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<2> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(2)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(2) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(2)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<1>::castAndCall(ptr, f);
		}
	}
};



template <> struct unrolled_dynamic_visitor<1> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(1)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(1) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(1)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<0>::castAndCall(ptr, f);
		}
	}
};


template <> struct unrolled_dynamic_visitor<0> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F &f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(0)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(0) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(0)>(ptr));
			f(entity);
		}
		else {
			std::cout << "Error!" << std::endl;
		}
	}
};