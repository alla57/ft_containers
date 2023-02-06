// unused or deleted functions

// vector
void	_realloc_and_insert(pointer pos, const value_type& value)
		{
			size_type new_capacity = _check_length(1);
			pointer tmp_start = _allocate(new_capacity);
			size_type old_size = size();
			size_type new_pos = pos - _start;
			std::uninitialized_copy(_start, pos, tmp_start);
			_construct(tmp_start + new_pos, value);
			std::uninitialized_copy(pos, _finish, tmp_start + pos + 1);
			_range_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = tmp_start;
			_end_of_storage = _start + new_capacity;
			_finish = _start + old_size + 1;
		}